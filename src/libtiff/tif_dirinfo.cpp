/* $Id: tif_dirinfo.c,v 1.127 2017-06-01 12:44:04 erouault Exp $ */

/*
 * Copyright (c) 1988-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

/*
 * TIFF Library.
 *
 * Core Directory Tag Support.
 */
#include "tiffiop.h"
#include <cstdlib>

/*
 * NOTE: THIS ARRAY IS ASSUMED TO BE SORTED BY TAG.
 *
 * NOTE: The second field (field_readcount) and third field (field_writecount)
 *       sometimes use the values TIFF_VARIABLE (-1), TIFF_VARIABLE2 (-3)
 *       and TIFF_SPP (-2). The macros should be used but would throw off
 *       the formatting of the code, so please interpret the -1, -2 and -3
 *       values accordingly.
 */
/* const object should be initialized */

static const TIFFField tiffFields[] = {
		{TIFFTAG_SUBFILETYPE,                1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_SUBFILETYPE,      1, 0, strdup("SubfileType"),               nullptr},
		{TIFFTAG_OSUBFILETYPE,               1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_SUBFILETYPE,      1, 0, strdup("OldSubfileType"),            nullptr},
		{TIFFTAG_IMAGEWIDTH,                 1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_IMAGEDIMENSIONS,  0, 0, strdup("ImageWidth"),                nullptr},
		{TIFFTAG_IMAGELENGTH,                1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_IMAGEDIMENSIONS,  1, 0, strdup("ImageLength"),               nullptr},
		{TIFFTAG_BITSPERSAMPLE,              -1, -1, TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_BITSPERSAMPLE,    0, 0, strdup("BitsPerSample"),             nullptr},
		{TIFFTAG_COMPRESSION,                -1, 1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_COMPRESSION,      0, 0, strdup("Compression"),               nullptr},
		{TIFFTAG_PHOTOMETRIC,                1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_PHOTOMETRIC,      0, 0, strdup("PhotometricInterpretation"), nullptr},
		{TIFFTAG_THRESHHOLDING,              1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_THRESHHOLDING,    1, 0, strdup("Threshholding"),             nullptr},
		{TIFFTAG_CELLWIDTH,                  1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_IGNORE,           1, 0, strdup("CellWidth"),                 nullptr},
		{TIFFTAG_CELLLENGTH,                 1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_IGNORE,           1, 0, strdup("CellLength"),                nullptr},
		{TIFFTAG_FILLORDER,                  1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_FILLORDER,        0, 0, strdup("FillOrder"),                 nullptr},
		{TIFFTAG_DOCUMENTNAME,               -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("DocumentName"),              nullptr},
		{TIFFTAG_IMAGEDESCRIPTION,           -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("ImageDescription"),          nullptr},
		{TIFFTAG_MAKE,                       -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("Make"),                      nullptr},
		{TIFFTAG_MODEL,                      -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("Model"),                     nullptr},
		{TIFFTAG_STRIPOFFSETS,               -1, -1, TIFF_LONG8,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_STRIPOFFSETS,     0, 0, strdup("StripOffsets"),              nullptr},
		{TIFFTAG_ORIENTATION,                1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_ORIENTATION,      0, 0, strdup("Orientation"),               nullptr},
		{TIFFTAG_SAMPLESPERPIXEL,            1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_SAMPLESPERPIXEL,  0, 0, strdup("SamplesPerPixel"),           nullptr},
		{TIFFTAG_ROWSPERSTRIP,               1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_ROWSPERSTRIP,     0, 0, strdup("RowsPerStrip"),              nullptr},
		{TIFFTAG_STRIPBYTECOUNTS,            -1, -1, TIFF_LONG8,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_STRIPBYTECOUNTS,  0, 0, strdup("StripByteCounts"),           nullptr},
		{TIFFTAG_MINSAMPLEVALUE,             -2, -1, TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_MINSAMPLEVALUE,   1, 0, strdup("MinSampleValue"),            nullptr},
		{TIFFTAG_MAXSAMPLEVALUE,             -2, -1, TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_MAXSAMPLEVALUE,   1, 0, strdup("MaxSampleValue"),            nullptr},
		{TIFFTAG_XRESOLUTION,                1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_RESOLUTION,       1, 0, strdup("XResolution"),               nullptr},
		{TIFFTAG_YRESOLUTION,                1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_RESOLUTION,       1, 0, strdup("YResolution"),               nullptr},
		{TIFFTAG_PLANARCONFIG,               1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_PLANARCONFIG,     0, 0, strdup("PlanarConfiguration"),       nullptr},
		{TIFFTAG_PAGENAME,                   -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("PageName"),                  nullptr},
		{TIFFTAG_XPOSITION,                  1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_POSITION,         1, 0, strdup("XPosition"),                 nullptr},
		{TIFFTAG_YPOSITION,                  1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_POSITION,         1, 0, strdup("YPosition"),                 nullptr},
		{TIFFTAG_FREEOFFSETS,                -1, -1, TIFF_LONG8,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_IGNORE,           0, 0, strdup("FreeOffsets"),               nullptr},
		{TIFFTAG_FREEBYTECOUNTS,             -1, -1, TIFF_LONG8,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_IGNORE,           0, 0, strdup("FreeByteCounts"),            nullptr},
		{TIFFTAG_GRAYRESPONSEUNIT,           1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_IGNORE,           1, 0, strdup("GrayResponseUnit"),          nullptr},
		{TIFFTAG_GRAYRESPONSECURVE,          -1, -1, TIFF_SHORT,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_IGNORE,           1, 0, strdup("GrayResponseCurve"),         nullptr},
		{TIFFTAG_RESOLUTIONUNIT,             1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_RESOLUTIONUNIT,   1, 0, strdup("ResolutionUnit"),            nullptr},
		{TIFFTAG_PAGENUMBER,                 2,  2,  TIFF_SHORT,     0, TIFF_SETGET_UINT16_PAIR, TIFF_SETGET_UNDEFINED, FIELD_PAGENUMBER,       1, 0, strdup("PageNumber"),                nullptr},
		{TIFFTAG_COLORRESPONSEUNIT,          1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_IGNORE,           1, 0, strdup("ColorResponseUnit"),         nullptr},
		{TIFFTAG_TRANSFERFUNCTION,           -1, -1, TIFF_SHORT,     0, TIFF_SETGET_OTHER,       TIFF_SETGET_UNDEFINED, FIELD_TRANSFERFUNCTION, 1, 0, strdup("TransferFunction"),          nullptr},
		{TIFFTAG_SOFTWARE,                   -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("Software"),                  nullptr},
		{TIFFTAG_DATETIME,                   20, 20, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("DateTime"),                  nullptr},
		{TIFFTAG_ARTIST,                     -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("Artist"),                    nullptr},
		{TIFFTAG_HOSTCOMPUTER,               -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("HostComputer"),              nullptr},
		{TIFFTAG_WHITEPOINT,                 2,  2,  TIFF_RATIONAL,  0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("WhitePoint"),                nullptr},
		{TIFFTAG_PRIMARYCHROMATICITIES,      6,  6,  TIFF_RATIONAL,  0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("PrimaryChromaticities"),     nullptr},
		{TIFFTAG_COLORMAP,                   -1, -1, TIFF_SHORT,     0, TIFF_SETGET_OTHER,       TIFF_SETGET_UNDEFINED, FIELD_COLORMAP,         1, 0, strdup("ColorMap"),                  nullptr},
		{TIFFTAG_HALFTONEHINTS,              2,  2,  TIFF_SHORT,     0, TIFF_SETGET_UINT16_PAIR, TIFF_SETGET_UNDEFINED, FIELD_HALFTONEHINTS,    1, 0, strdup("HalftoneHints"),             nullptr},
		{TIFFTAG_TILEWIDTH,                  1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_TILEDIMENSIONS,   0, 0, strdup("TileWidth"),                 nullptr},
		{TIFFTAG_TILELENGTH,                 1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_TILEDIMENSIONS,   0, 0, strdup("TileLength"),                nullptr},
		{TIFFTAG_TILEOFFSETS,                -1, 1,  TIFF_LONG8,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_STRIPOFFSETS,     0, 0, strdup("TileOffsets"),               nullptr},
		{TIFFTAG_TILEBYTECOUNTS,             -1, 1,  TIFF_LONG8,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_STRIPBYTECOUNTS,  0, 0, strdup("TileByteCounts"),            nullptr},
		{TIFFTAG_SUBIFD,                     -1, -1, TIFF_IFD8,      0, TIFF_SETGET_C16_IFD8,    TIFF_SETGET_UNDEFINED, FIELD_SUBIFD,           1, 1, strdup("SubIFD"),                    (TIFFFieldArray *) &tiffFieldArray},
		{TIFFTAG_INKSET,                     1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("InkSet"),                    nullptr},
		{TIFFTAG_INKNAMES,                   -1, -1, TIFF_ASCII,     0, TIFF_SETGET_C16_ASCII,   TIFF_SETGET_UNDEFINED, FIELD_INKNAMES,         1, 1, strdup("InkNames"),                  nullptr},
		{TIFFTAG_NUMBEROFINKS,               1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("NumberOfInks"),              nullptr},
		{TIFFTAG_DOTRANGE,                   2,  2,  TIFF_SHORT,     0, TIFF_SETGET_UINT16_PAIR, TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("DotRange"),                  nullptr},
		{TIFFTAG_TARGETPRINTER,              -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("TargetPrinter"),             nullptr},
		{TIFFTAG_EXTRASAMPLES,               -1, -1, TIFF_SHORT,     0, TIFF_SETGET_C16_UINT16,  TIFF_SETGET_UNDEFINED, FIELD_EXTRASAMPLES,     0, 1, strdup("ExtraSamples"),              nullptr},
		{TIFFTAG_SAMPLEFORMAT,               -1, -1, TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_SAMPLEFORMAT,     0, 0, strdup("SampleFormat"),              nullptr},
		{TIFFTAG_SMINSAMPLEVALUE,            -2, -1, TIFF_ANY,       0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_SMINSAMPLEVALUE,  1, 0, strdup("SMinSampleValue"),           nullptr},
		{TIFFTAG_SMAXSAMPLEVALUE,            -2, -1, TIFF_ANY,       0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_SMAXSAMPLEVALUE,  1, 0, strdup("SMaxSampleValue"),           nullptr},
		{TIFFTAG_CLIPPATH,                   -1, -3, TIFF_BYTE,      0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("ClipPath"),                  nullptr},
		{TIFFTAG_XCLIPPATHUNITS,             1,  1,  TIFF_SLONG,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("XClipPathUnits"),            nullptr},
		{TIFFTAG_XCLIPPATHUNITS,             1,  1,  TIFF_SBYTE,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("XClipPathUnits"),            nullptr},
		{TIFFTAG_YCLIPPATHUNITS,             1,  1,  TIFF_SLONG,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("YClipPathUnits"),            nullptr},
		{TIFFTAG_YCBCRCOEFFICIENTS,          3,  3,  TIFF_RATIONAL,  0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("YCbCrCoefficients"),         nullptr},
		{TIFFTAG_YCBCRSUBSAMPLING,           2,  2,  TIFF_SHORT,     0, TIFF_SETGET_UINT16_PAIR, TIFF_SETGET_UNDEFINED, FIELD_YCBCRSUBSAMPLING, 0, 0, strdup("YCbCrSubsampling"),          nullptr},
		{TIFFTAG_YCBCRPOSITIONING,           1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_YCBCRPOSITIONING, 0, 0, strdup("YCbCrPositioning"),          nullptr},
		{TIFFTAG_REFERENCEBLACKWHITE,        6,  6,  TIFF_RATIONAL,  0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_REFBLACKWHITE,    1, 0, strdup("ReferenceBlackWhite"),       nullptr},
		{TIFFTAG_XMLPACKET,                  -3, -3, TIFF_BYTE,      0, TIFF_SETGET_C32_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("XMLPacket"),                 nullptr},
		/* begin SGI tags */
		{TIFFTAG_MATTEING,                   1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_EXTRASAMPLES,     0, 0, strdup("Matteing"),                  nullptr},
		{TIFFTAG_DATATYPE,                   -2, -1, TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_SAMPLEFORMAT,     0, 0, strdup("DataType"),                  nullptr},
		{TIFFTAG_IMAGEDEPTH,                 1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_IMAGEDEPTH,       0, 0, strdup("ImageDepth"),                nullptr},
		{TIFFTAG_TILEDEPTH,                  1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_TILEDEPTH,        0, 0, strdup("TileDepth"),                 nullptr},
		/* end SGI tags */
		/* begin Pixar tags */
		{TIFFTAG_PIXAR_IMAGEFULLWIDTH,       1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("ImageFullWidth"),            nullptr},
		{TIFFTAG_PIXAR_IMAGEFULLLENGTH,      1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("ImageFullLength"),           nullptr},
		{TIFFTAG_PIXAR_TEXTUREFORMAT,        -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("TextureFormat"),             nullptr},
		{TIFFTAG_PIXAR_WRAPMODES,            -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("TextureWrapModes"),          nullptr},
		{TIFFTAG_PIXAR_FOVCOT,               1,  1,  TIFF_FLOAT,     0, TIFF_SETGET_FLOAT,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("FieldOfViewCotangent"),      nullptr},
		{TIFFTAG_PIXAR_MATRIX_WORLDTOSCREEN, 16, 16, TIFF_FLOAT,     0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("MatrixWorldToScreen"),       nullptr},
		{TIFFTAG_PIXAR_MATRIX_WORLDTOCAMERA, 16, 16, TIFF_FLOAT,     0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("MatrixWorldToCamera"),       nullptr},
		{TIFFTAG_CFAREPEATPATTERNDIM,        2,  2,  TIFF_SHORT,     0, TIFF_SETGET_C0_UINT16,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("CFARepeatPatternDim"),       nullptr},
		{TIFFTAG_CFAPATTERN,                 4,  4,  TIFF_BYTE,      0, TIFF_SETGET_C0_UINT8,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("CFAPattern"),                nullptr},
		{TIFFTAG_COPYRIGHT,                  -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("Copyright"),                 nullptr},
		/* end Pixar tags */
		{TIFFTAG_RICHTIFFIPTC,               -3, -3, TIFF_LONG,      0, TIFF_SETGET_C32_UINT32,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("RichTIFFIPTC"),              nullptr},
		{TIFFTAG_PHOTOSHOP,                  -3, -3, TIFF_BYTE,      0, TIFF_SETGET_C32_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("Photoshop"),                 nullptr},
		{TIFFTAG_EXIFIFD,                    1,  1,  TIFF_IFD8,      0, TIFF_SETGET_IFD8,        TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("EXIFIFDOffset"),             (TIFFFieldArray *) &exifFieldArray},
		{TIFFTAG_ICCPROFILE,                 -3, -3, TIFF_UNDEFINED, 0, TIFF_SETGET_C32_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("ICC Profile"),               nullptr},
		{TIFFTAG_GPSIFD,                     1,  1,  TIFF_IFD8,      0, TIFF_SETGET_IFD8,        TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("GPSIFDOffset"),              nullptr},
		{TIFFTAG_FAXRECVPARAMS,              1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UINT32,    FIELD_CUSTOM, TRUE, FALSE,    strdup("FaxRecvParams"),             nullptr},
		{TIFFTAG_FAXSUBADDRESS,              -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_ASCII,     FIELD_CUSTOM, TRUE, FALSE,    strdup("FaxSubAddress"),             nullptr},
		{TIFFTAG_FAXRECVTIME,                1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UINT32,    FIELD_CUSTOM, TRUE, FALSE,    strdup("FaxRecvTime"),               nullptr},
		{TIFFTAG_FAXDCS,                     -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_ASCII,     FIELD_CUSTOM, TRUE, FALSE,    strdup("FaxDcs"),                    nullptr},
		{TIFFTAG_STONITS,                    1,  1,  TIFF_DOUBLE,    0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("StoNits"),                   nullptr},
		{TIFFTAG_INTEROPERABILITYIFD,        1,  1,  TIFF_IFD8,      0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("InteroperabilityIFDOffset"), nullptr},
		/* begin DNG tags */
		{TIFFTAG_DNGVERSION,                 4,  4,  TIFF_BYTE,      0, TIFF_SETGET_C0_UINT8,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("DNGVersion"),                nullptr},
		{TIFFTAG_DNGBACKWARDVERSION,         4,  4,  TIFF_BYTE,      0, TIFF_SETGET_C0_UINT8,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("DNGBackwardVersion"),        nullptr},
		{TIFFTAG_UNIQUECAMERAMODEL,          -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("UniqueCameraModel"),         nullptr},
		{TIFFTAG_LOCALIZEDCAMERAMODEL,       -1, -1, TIFF_BYTE,      0, TIFF_SETGET_C16_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 1, strdup("LocalizedCameraModel"),      nullptr},
		{TIFFTAG_CFAPLANECOLOR,              -1, -1, TIFF_BYTE,      0, TIFF_SETGET_C16_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("CFAPlaneColor"),             nullptr},
		{TIFFTAG_CFALAYOUT,                  1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("CFALayout"),                 nullptr},
		{TIFFTAG_LINEARIZATIONTABLE,         -1, -1, TIFF_SHORT,     0, TIFF_SETGET_C16_UINT16,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("LinearizationTable"),        nullptr},
		{TIFFTAG_BLACKLEVELREPEATDIM,        2,  2,  TIFF_SHORT,     0, TIFF_SETGET_C0_UINT16,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("BlackLevelRepeatDim"),       nullptr},
		{TIFFTAG_BLACKLEVEL,                 -1, -1, TIFF_RATIONAL,  0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("BlackLevel"),                nullptr},
		{TIFFTAG_BLACKLEVELDELTAH,           -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("BlackLevelDeltaH"),          nullptr},
		{TIFFTAG_BLACKLEVELDELTAV,           -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("BlackLevelDeltaV"),          nullptr},
		{TIFFTAG_WHITELEVEL,                 -1, -1, TIFF_LONG,      0, TIFF_SETGET_C16_UINT32,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("WhiteLevel"),                nullptr},
		{TIFFTAG_DEFAULTSCALE,               2,  2,  TIFF_RATIONAL,  0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("DefaultScale"),              nullptr},
		{TIFFTAG_BESTQUALITYSCALE,           1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("BestQualityScale"),          nullptr},
		{TIFFTAG_DEFAULTCROPORIGIN,          2,  2,  TIFF_RATIONAL,  0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("DefaultCropOrigin"),         nullptr},
		{TIFFTAG_DEFAULTCROPSIZE,            2,  2,  TIFF_RATIONAL,  0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("DefaultCropSize"),           nullptr},
		{TIFFTAG_COLORMATRIX1,               -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("ColorMatrix1"),              nullptr},
		{TIFFTAG_COLORMATRIX2,               -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("ColorMatrix2"),              nullptr},
		{TIFFTAG_CAMERACALIBRATION1,         -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("CameraCalibration1"),        nullptr},
		{TIFFTAG_CAMERACALIBRATION2,         -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("CameraCalibration2"),        nullptr},
		{TIFFTAG_REDUCTIONMATRIX1,           -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("ReductionMatrix1"),          nullptr},
		{TIFFTAG_REDUCTIONMATRIX2,           -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("ReductionMatrix2"),          nullptr},
		{TIFFTAG_ANALOGBALANCE,              -1, -1, TIFF_RATIONAL,  0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("AnalogBalance"),             nullptr},
		{TIFFTAG_ASSHOTNEUTRAL,              -1, -1, TIFF_RATIONAL,  0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("AsShotNeutral"),             nullptr},
		{TIFFTAG_ASSHOTWHITEXY,              2,  2,  TIFF_RATIONAL,  0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("AsShotWhiteXY"),             nullptr},
		{TIFFTAG_BASELINEEXPOSURE,           1,  1,  TIFF_SRATIONAL, 0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("BaselineExposure"),          nullptr},
		{TIFFTAG_BASELINENOISE,              1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("BaselineNoise"),             nullptr},
		{TIFFTAG_BASELINESHARPNESS,          1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("BaselineSharpness"),         nullptr},
		{TIFFTAG_BAYERGREENSPLIT,            1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("BayerGreenSplit"),           nullptr},
		{TIFFTAG_LINEARRESPONSELIMIT,        1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("LinearResponseLimit"),       nullptr},
		{TIFFTAG_CAMERASERIALNUMBER,         -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 0, strdup("CameraSerialNumber"),        nullptr},
		{TIFFTAG_LENSINFO,                   4,  4,  TIFF_RATIONAL,  0, TIFF_SETGET_C0_FLOAT,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("LensInfo"),                  nullptr},
		{TIFFTAG_CHROMABLURRADIUS,           1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("ChromaBlurRadius"),          nullptr},
		{TIFFTAG_ANTIALIASSTRENGTH,          1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("AntiAliasStrength"),         nullptr},
		{TIFFTAG_SHADOWSCALE,                1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("ShadowScale"),               nullptr},
		{TIFFTAG_DNGPRIVATEDATA,             -1, -1, TIFF_BYTE,      0, TIFF_SETGET_C16_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("DNGPrivateData"),            nullptr},
		{TIFFTAG_MAKERNOTESAFETY,            1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("MakerNoteSafety"),           nullptr},
		{TIFFTAG_CALIBRATIONILLUMINANT1,     1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("CalibrationIlluminant1"),    nullptr},
		{TIFFTAG_CALIBRATIONILLUMINANT2,     1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("CalibrationIlluminant2"),    nullptr},
		{TIFFTAG_RAWDATAUNIQUEID,            16, 16, TIFF_BYTE,      0, TIFF_SETGET_C0_UINT8,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("RawDataUniqueID"),           nullptr},
		{TIFFTAG_ORIGINALRAWFILENAME,        -1, -1, TIFF_BYTE,      0, TIFF_SETGET_C16_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           1, 1, strdup("OriginalRawFileName"),       nullptr},
		{TIFFTAG_ORIGINALRAWFILEDATA,        -1, -1, TIFF_UNDEFINED, 0, TIFF_SETGET_C16_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("OriginalRawFileData"),       nullptr},
		{TIFFTAG_ACTIVEAREA,                 4,  4,  TIFF_LONG,      0, TIFF_SETGET_C0_UINT32,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("ActiveArea"),                nullptr},
		{TIFFTAG_MASKEDAREAS,                -1, -1, TIFF_LONG,      0, TIFF_SETGET_C16_UINT32,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("MaskedAreas"),               nullptr},
		{TIFFTAG_ASSHOTICCPROFILE,           -1, -1, TIFF_UNDEFINED, 0, TIFF_SETGET_C16_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("AsShotICCProfile"),          nullptr},
		{TIFFTAG_ASSHOTPREPROFILEMATRIX,     -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("AsShotPreProfileMatrix"),    nullptr},
		{TIFFTAG_CURRENTICCPROFILE,          -1, -1, TIFF_UNDEFINED, 0, TIFF_SETGET_C16_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("CurrentICCProfile"),         nullptr},
		{TIFFTAG_CURRENTPREPROFILEMATRIX,    -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("CurrentPreProfileMatrix"),   nullptr},
		{TIFFTAG_PERSAMPLE,                  0,  0,  TIFF_SHORT,     0, TIFF_SETGET_UNDEFINED,   TIFF_SETGET_UNDEFINED, FIELD_PSEUDO, TRUE, FALSE,    strdup("PerSample"),                 nullptr},
		/* end DNG tags */
		/* begin TIFF/FX tags */
		{TIFFTAG_INDEXED,                    1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("Indexed"),                   nullptr},
		{TIFFTAG_GLOBALPARAMETERSIFD,        1,  1,  TIFF_IFD8,      0, TIFF_SETGET_IFD8,        TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("GlobalParametersIFD"),       nullptr},
		{TIFFTAG_PROFILETYPE,                1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("ProfileType"),               nullptr},
		{TIFFTAG_FAXPROFILE,                 1,  1,  TIFF_BYTE,      0, TIFF_SETGET_UINT8,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("FaxProfile"),                nullptr},
		{TIFFTAG_CODINGMETHODS,              1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("CodingMethods"),             nullptr},
		{TIFFTAG_VERSIONYEAR,                4,  4,  TIFF_BYTE,      0, TIFF_SETGET_C0_UINT8,    TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("VersionYear"),               nullptr},
		{TIFFTAG_MODENUMBER,                 1,  1,  TIFF_BYTE,      0, TIFF_SETGET_UINT8,       TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("ModeNumber"),                nullptr},
		{TIFFTAG_DECODE,                     -1, -1, TIFF_SRATIONAL, 0, TIFF_SETGET_C16_FLOAT,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("Decode"),                    nullptr},
		{TIFFTAG_IMAGEBASECOLOR,             -1, -1, TIFF_SHORT,     0, TIFF_SETGET_C16_UINT16,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("ImageBaseColor"),            nullptr},
		{TIFFTAG_T82OPTIONS,                 1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("T82Options"),                nullptr},
		{TIFFTAG_STRIPROWCOUNTS,             -1, -1, TIFF_LONG,      0, TIFF_SETGET_C16_UINT32,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 1, strdup("StripRowCounts"),            nullptr},
		{TIFFTAG_IMAGELAYER,                 2,  2,  TIFF_LONG,      0, TIFF_SETGET_C0_UINT32,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM,           0, 0, strdup("ImageLayer"),                nullptr},
		/* end TIFF/FX tags */
		/* begin pseudo tags */
};

static const TIFFField
		exifFields[] = {
		{EXIFTAG_EXPOSURETIME,             1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ExposureTime"),                 nullptr},
		{EXIFTAG_FNUMBER,                  1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("FNumber"),                      nullptr},
		{EXIFTAG_EXPOSUREPROGRAM,          1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ExposureProgram"),              nullptr},
		{EXIFTAG_SPECTRALSENSITIVITY,      -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SpectralSensitivity"),          nullptr},
		{EXIFTAG_ISOSPEEDRATINGS,          -1, -1, TIFF_SHORT,     0, TIFF_SETGET_C16_UINT16, TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 1, strdup("ISOSpeedRatings"),              nullptr},
		{EXIFTAG_OECF,                     -1, -1, TIFF_UNDEFINED, 0, TIFF_SETGET_C16_UINT8,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 1, strdup("OptoelectricConversionFactor"), nullptr},
		{EXIFTAG_EXIFVERSION,              4,  4,  TIFF_UNDEFINED, 0, TIFF_SETGET_C0_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ExifVersion"),                  nullptr},
		{EXIFTAG_DATETIMEORIGINAL,         20, 20, TIFF_ASCII,     0, TIFF_SETGET_ASCII,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("DateTimeOriginal"),             nullptr},
		{EXIFTAG_DATETIMEDIGITIZED,        20, 20, TIFF_ASCII,     0, TIFF_SETGET_ASCII,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("DateTimeDigitized"),            nullptr},
		{EXIFTAG_COMPONENTSCONFIGURATION,  4,  4,  TIFF_UNDEFINED, 0, TIFF_SETGET_C0_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ComponentsConfiguration"),      nullptr},
		{EXIFTAG_COMPRESSEDBITSPERPIXEL,   1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("CompressedBitsPerPixel"),       nullptr},
		{EXIFTAG_SHUTTERSPEEDVALUE,        1,  1,  TIFF_SRATIONAL, 0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ShutterSpeedValue"),            nullptr},
		{EXIFTAG_APERTUREVALUE,            1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ApertureValue"),                nullptr},
		{EXIFTAG_BRIGHTNESSVALUE,          1,  1,  TIFF_SRATIONAL, 0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("BrightnessValue"),              nullptr},
		{EXIFTAG_EXPOSUREBIASVALUE,        1,  1,  TIFF_SRATIONAL, 0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ExposureBiasValue"),            nullptr},
		{EXIFTAG_MAXAPERTUREVALUE,         1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("MaxApertureValue"),             nullptr},
		{EXIFTAG_SUBJECTDISTANCE,          1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SubjectDistance"),              nullptr},
		{EXIFTAG_METERINGMODE,             1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("MeteringMode"),                 nullptr},
		{EXIFTAG_LIGHTSOURCE,              1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("LightSource"),                  nullptr},
		{EXIFTAG_FLASH,                    1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("Flash"),                        nullptr},
		{EXIFTAG_FOCALLENGTH,              1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("FocalLength"),                  nullptr},
		{EXIFTAG_SUBJECTAREA,              -1, -1, TIFF_SHORT,     0, TIFF_SETGET_C16_UINT16, TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 1, strdup("SubjectArea"),                  nullptr},
		{EXIFTAG_MAKERNOTE,                -1, -1, TIFF_UNDEFINED, 0, TIFF_SETGET_C16_UINT8,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 1, strdup("MakerNote"),                    nullptr},
		{EXIFTAG_USERCOMMENT,              -1, -1, TIFF_UNDEFINED, 0, TIFF_SETGET_C16_UINT8,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 1, strdup("UserComment"),                  nullptr},
		{EXIFTAG_SUBSECTIME,               -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SubSecTime"),                   nullptr},
		{EXIFTAG_SUBSECTIMEORIGINAL,       -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SubSecTimeOriginal"),           nullptr},
		{EXIFTAG_SUBSECTIMEDIGITIZED,      -1, -1, TIFF_ASCII,     0, TIFF_SETGET_ASCII,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SubSecTimeDigitized"),          nullptr},
		{EXIFTAG_FLASHPIXVERSION,          4,  4,  TIFF_UNDEFINED, 0, TIFF_SETGET_C0_UINT8,   TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("FlashpixVersion"),              nullptr},
		{EXIFTAG_COLORSPACE,               1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ColorSpace"),                   nullptr},
		{EXIFTAG_PIXELXDIMENSION,          1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("PixelXDimension"),              nullptr},
		{EXIFTAG_PIXELYDIMENSION,          1,  1,  TIFF_LONG,      0, TIFF_SETGET_UINT32,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("PixelYDimension"),              nullptr},
		{EXIFTAG_RELATEDSOUNDFILE,         13, 13, TIFF_ASCII,     0, TIFF_SETGET_ASCII,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("RelatedSoundFile"),             nullptr},
		{EXIFTAG_FLASHENERGY,              1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("FlashEnergy"),                  nullptr},
		{EXIFTAG_SPATIALFREQUENCYRESPONSE, -1, -1, TIFF_UNDEFINED, 0, TIFF_SETGET_C16_UINT8,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 1, strdup("SpatialFrequencyResponse"),     nullptr},
		{EXIFTAG_FOCALPLANEXRESOLUTION,    1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("FocalPlaneXResolution"),        nullptr},
		{EXIFTAG_FOCALPLANEYRESOLUTION,    1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("FocalPlaneYResolution"),        nullptr},
		{EXIFTAG_FOCALPLANERESOLUTIONUNIT, 1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("FocalPlaneResolutionUnit"),     nullptr},
		{EXIFTAG_SUBJECTLOCATION,          2,  2,  TIFF_SHORT,     0, TIFF_SETGET_C0_UINT16,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SubjectLocation"),              nullptr},
		{EXIFTAG_EXPOSUREINDEX,            1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ExposureIndex"),                nullptr},
		{EXIFTAG_SENSINGMETHOD,            1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SensingMethod"),                nullptr},
		{EXIFTAG_FILESOURCE,               1,  1,  TIFF_UNDEFINED, 0, TIFF_SETGET_UINT8,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("FileSource"),                   nullptr},
		{EXIFTAG_SCENETYPE,                1,  1,  TIFF_UNDEFINED, 0, TIFF_SETGET_UINT8,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SceneType"),                    nullptr},
		{EXIFTAG_CFAPATTERN,               -1, -1, TIFF_UNDEFINED, 0, TIFF_SETGET_C16_UINT8,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 1, strdup("CFAPattern"),                   nullptr},
		{EXIFTAG_CUSTOMRENDERED,           1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("CustomRendered"),               nullptr},
		{EXIFTAG_EXPOSUREMODE,             1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ExposureMode"),                 nullptr},
		{EXIFTAG_WHITEBALANCE,             1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("WhiteBalance"),                 nullptr},
		{EXIFTAG_DIGITALZOOMRATIO,         1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("DigitalZoomRatio"),             nullptr},
		{EXIFTAG_FOCALLENGTHIN35MMFILM,    1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("FocalLengthIn35mmFilm"),        nullptr},
		{EXIFTAG_SCENECAPTURETYPE,         1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SceneCaptureType"),             nullptr},
		{EXIFTAG_GAINCONTROL,              1,  1,  TIFF_RATIONAL,  0, TIFF_SETGET_DOUBLE,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("GainControl"),                  nullptr},
		{EXIFTAG_CONTRAST,                 1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("Contrast"),                     nullptr},
		{EXIFTAG_SATURATION,               1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("Saturation"),                   nullptr},
		{EXIFTAG_SHARPNESS,                1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("Sharpness"),                    nullptr},
		{EXIFTAG_DEVICESETTINGDESCRIPTION, -1, -1, TIFF_UNDEFINED, 0, TIFF_SETGET_C16_UINT8,  TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 1, strdup("DeviceSettingDescription"),     nullptr},
		{EXIFTAG_SUBJECTDISTANCERANGE,     1,  1,  TIFF_SHORT,     0, TIFF_SETGET_UINT16,     TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("SubjectDistanceRange"),         nullptr},
		{EXIFTAG_IMAGEUNIQUEID,            33, 33, TIFF_ASCII,     0, TIFF_SETGET_ASCII,      TIFF_SETGET_UNDEFINED, FIELD_CUSTOM, 1, 0, strdup("ImageUniqueID"),                nullptr}
};
const TIFFFieldArray
		tiffFieldArray = {tfiatImage, 0, TIFFArrayCount(tiffFields), (TIFFField *) tiffFields};
const TIFFFieldArray
		exifFieldArray = {tfiatExif, 0, TIFFArrayCount(exifFields), (TIFFField *) exifFields};

/*
 *  We have our own local lfind() equivalent to avoid subtle differences
 *  in types passed to lfind() on different systems. 
 */

static void *
td_lfind(const void *key, const void *base, size_t *nmemb, size_t size,
		int(*compar)(const void *, const void *)) {
	char *element, *end;

	end = (char *) base + *nmemb * size;
	for (element = (char *) base; element < end; element += size)
		if (!compar(key, element))        /* key found */
			return element;

	return nullptr;
}

const TIFFFieldArray *
_TIFFGetFields(void) {
	return (&tiffFieldArray);
}

const TIFFFieldArray *
_TIFFGetExifFields(void) {
	return (&exifFieldArray);
}

void
_TIFFSetupFields(TIFF *tif, const TIFFFieldArray *fieldarray) {
	if (tif->tif_fields && tif->tif_nfields > 0) {
		uint32 i;

		for (i = 0; i < tif->tif_nfields; i++) {
			TIFFField *fld = tif->tif_fields[i];
			if (fld->field_bit == FIELD_CUSTOM &&
			    strncmp("Tag ", fld->field_name, 4) == 0) {
				_TIFFfree(fld->field_name);
				_TIFFfree(fld);
			}
		}

		_TIFFfree(tif->tif_fields);
		tif->tif_fields = nullptr;
		tif->tif_nfields = 0;
	}
	if (!_TIFFMergeFields(tif, fieldarray->fields, fieldarray->count)) {
		TIFFErrorExt(tif->tif_clientdata, "_TIFFSetupFields",
		             "Setting up field info failed");
	}
}

static int
tagCompare(const void *a, const void *b) {
	const TIFFField *ta = *(const TIFFField **) a;
	const TIFFField *tb = *(const TIFFField **) b;
	/* NB: be careful of return values for 16-bit platforms */
	if (ta->field_tag != tb->field_tag)
		return (int) ta->field_tag - (int) tb->field_tag;
	else
		return (ta->field_type == TIFF_ANY) ?
		       0 : ((int) tb->field_type - (int) ta->field_type);
}

static int
tagNameCompare(const void *a, const void *b) {
	const TIFFField *ta = *(const TIFFField **) a;
	const TIFFField *tb = *(const TIFFField **) b;
	int ret = strcmp(ta->field_name, tb->field_name);

	if (ret)
		return ret;
	else
		return (ta->field_type == TIFF_ANY) ?
		       0 : ((int) tb->field_type - (int) ta->field_type);
}

int
_TIFFMergeFields(TIFF *tif, const TIFFField info[], uint32 n) {
	static const char module[] = "_TIFFMergeFields";
	static const char reason[] = "for fields array";
	/* TIFFField** tp; */
	uint32 i;

	tif->tif_foundfield = nullptr;

	if (tif->tif_fields && tif->tif_nfields > 0) {
		tif->tif_fields = (TIFFField **)
				_TIFFCheckRealloc(tif, tif->tif_fields,
				                  (tif->tif_nfields + n),
				                  sizeof(TIFFField *), reason);
	} else {
		tif->tif_fields = (TIFFField **)
				_TIFFCheckMalloc(tif, n, sizeof(TIFFField *),
				                 reason);
	}
	if (!tif->tif_fields) {
		TIFFErrorExt(tif->tif_clientdata, module,
		             "Failed to allocate fields array");
		return 0;
	}

	/* tp = tif->tif_fields + tif->tif_nfields; */
	for (i = 0; i < n; i++) {
		const TIFFField *fip =
				TIFFFindField(tif, info[i].field_tag, TIFF_ANY);

		/* only add definitions that aren't already present */
		if (!fip) {
			tif->tif_fields[tif->tif_nfields] = (TIFFField *) (info + i);
			tif->tif_nfields++;
		}
	}

	/* Sort the field info by tag number */
	qsort(tif->tif_fields, tif->tif_nfields,
	      sizeof(TIFFField *), tagCompare);

	return n;
}

void
_TIFFPrintFieldInfo(TIFF *tif, FILE *fd) {
	uint32 i;

	fprintf(fd, "%s: \n", tif->tif_name);
	for (i = 0; i < tif->tif_nfields; i++) {
		const TIFFField *fip = tif->tif_fields[i];
		fprintf(fd, "field[%2d] %5lu, %2d, %2d, %d, %2d, %5s, %5s, %s\n", (int) i, (unsigned long) fip->field_tag, fip->field_readcount, fip->field_writecount, fip->field_type, fip->field_bit, fip->field_oktochange
		                                                                                                                                                                                         ? "TRUE"
		                                                                                                                                                                                         : "FALSE", fip->field_passcount
		                                                                                                                                                                                                    ? "TRUE"
		                                                                                                                                                                                                    : "FALSE", fip->field_name
		);
	}
}

/*
 * Return size of TIFFDataType in bytes
 */
int
TIFFDataWidth(TIFFDataType type) {
	switch (type) {
		case 0:  /* nothing */
		case TIFF_BYTE:
		case TIFF_ASCII:
		case TIFF_SBYTE:
		case TIFF_UNDEFINED:
			return 1;
		case TIFF_SHORT:
		case TIFF_SSHORT:
			return 2;
		case TIFF_LONG:
		case TIFF_SLONG:
		case TIFF_FLOAT:
		case TIFF_IFD:
			return 4;
		case TIFF_RATIONAL:
		case TIFF_SRATIONAL:
		case TIFF_DOUBLE:
		case TIFF_LONG8:
		case TIFF_SLONG8:
		case TIFF_IFD8:
			return 8;
		default:
			return 0; /* will return 0 for unknown types */
	}
}

/*
 * Return size of TIFFDataType in bytes.
 *
 * XXX: We need a separate function to determine the space needed
 * to store the value. For TIFF_RATIONAL values TIFFDataWidth() returns 8,
 * but we use 4-byte float to represent rationals.
 */
int
_TIFFDataSize(TIFFDataType type) {
	switch (type) {
		case TIFF_BYTE:
		case TIFF_SBYTE:
		case TIFF_ASCII:
		case TIFF_UNDEFINED:
			return 1;
		case TIFF_SHORT:
		case TIFF_SSHORT:
			return 2;
		case TIFF_LONG:
		case TIFF_SLONG:
		case TIFF_FLOAT:
		case TIFF_IFD:
		case TIFF_RATIONAL:
		case TIFF_SRATIONAL:
			return 4;
		case TIFF_DOUBLE:
		case TIFF_LONG8:
		case TIFF_SLONG8:
		case TIFF_IFD8:
			return 8;
		default:
			return 0;
	}
}

const TIFFField *
TIFFFindField(TIFF *tif, uint32 tag, TIFFDataType dt) {
	TIFFField key = {0, 0, 0, TIFF_NOTYPE, 0, TIFF_SETGET_UNDEFINED, TIFF_SETGET_UNDEFINED, 0, 0, 0, nullptr, nullptr};
	TIFFField *pkey = &key;
	const TIFFField **ret;
	if (tif->tif_foundfield && tif->tif_foundfield->field_tag == tag &&
	    (dt == TIFF_ANY || dt == tif->tif_foundfield->field_type))
		return tif->tif_foundfield;

	/* If we are invoked with no field information, then just return. */
	if (!tif->tif_fields)
		return nullptr;

	/* NB: use sorted search (e.g. binary search) */

	key.field_tag = tag;
	key.field_type = dt;

	ret = (const TIFFField **) bsearch(&pkey, tif->tif_fields,
	                                   tif->tif_nfields,
	                                   sizeof(TIFFField *), tagCompare);
	return tif->tif_foundfield = (ret ? *ret : nullptr);
}

static const TIFFField *
_TIFFFindFieldByName(TIFF *tif, const char *field_name, TIFFDataType dt) {
	TIFFField key = {0, 0, 0, TIFF_NOTYPE, 0, TIFF_SETGET_UNDEFINED, TIFF_SETGET_UNDEFINED, 0, 0, 0, nullptr, nullptr};
	TIFFField *pkey = &key;
	const TIFFField **ret;
	if (tif->tif_foundfield
	    && streq(tif->tif_foundfield->field_name, field_name)
	    && (dt == TIFF_ANY || dt == tif->tif_foundfield->field_type))
		return (tif->tif_foundfield);

	/* If we are invoked with no field information, then just return. */
	if (!tif->tif_fields)
		return nullptr;

	/* NB: use linear search since list is sorted by key#, not name */

	key.field_name = (char *) field_name;
	key.field_type = dt;

	ret = (const TIFFField **)
			td_lfind(&pkey, tif->tif_fields, &tif->tif_nfields,
			         sizeof(TIFFField *), tagNameCompare);

	return tif->tif_foundfield = (ret ? *ret : nullptr);
}

const TIFFField *
TIFFFieldWithTag(TIFF *tif, uint32 tag) {
	const TIFFField *fip = TIFFFindField(tif, tag, TIFF_ANY);
	if (!fip) {
		TIFFErrorExt(tif->tif_clientdata, "TIFFFieldWithTag",
		             "Internal error, unknown tag 0x%x",
		             (unsigned int) tag);
	}
	return (fip);
}

const TIFFField *
TIFFFieldWithName(TIFF *tif, const char *field_name) {
	const TIFFField *fip =
			_TIFFFindFieldByName(tif, field_name, TIFF_ANY);
	if (!fip) {
		TIFFErrorExt(tif->tif_clientdata, "TIFFFieldWithName",
		             "Internal error, unknown tag %s", field_name);
	}
	return (fip);
}

uint32
TIFFFieldTag(const TIFFField *fip) {
	return fip->field_tag;
}

const char *
TIFFFieldName(const TIFFField *fip) {
	return fip->field_name;
}

TIFFDataType
TIFFFieldDataType(const TIFFField *fip) {
	return fip->field_type;
}

int
TIFFFieldPassCount(const TIFFField *fip) {
	return fip->field_passcount;
}

int
TIFFFieldReadCount(const TIFFField *fip) {
	return fip->field_readcount;
}

int
TIFFFieldWriteCount(const TIFFField *fip) {
	return fip->field_writecount;
}

const TIFFField *
_TIFFFindOrRegisterField(TIFF *tif, uint32 tag, TIFFDataType dt) {
	const TIFFField *fld;

	fld = TIFFFindField(tif, tag, dt);
	if (fld == nullptr) {
		fld = _TIFFCreateAnonField(tif, tag, dt);
		if (!_TIFFMergeFields(tif, fld, 1))
			return nullptr;
	}

	return fld;
}

TIFFField *
_TIFFCreateAnonField(TIFF *tif, uint32 tag, TIFFDataType field_type) {
	TIFFField *fld;
	(void) tif;

	fld = (TIFFField *) _TIFFmalloc(sizeof(TIFFField));
	if (fld == nullptr)
		return nullptr;
	_TIFFmemset(fld, 0, sizeof(TIFFField));

	fld->field_tag = tag;
	fld->field_readcount = TIFF_VARIABLE2;
	fld->field_writecount = TIFF_VARIABLE2;
	fld->field_type = field_type;
	fld->reserved = 0;
	switch (field_type) {
		case TIFF_BYTE:
		case TIFF_UNDEFINED:
			fld->set_field_type = TIFF_SETGET_C32_UINT8;
			fld->get_field_type = TIFF_SETGET_C32_UINT8;
			break;
		case TIFF_ASCII:
			fld->set_field_type = TIFF_SETGET_C32_ASCII;
			fld->get_field_type = TIFF_SETGET_C32_ASCII;
			break;
		case TIFF_SHORT:
			fld->set_field_type = TIFF_SETGET_C32_UINT16;
			fld->get_field_type = TIFF_SETGET_C32_UINT16;
			break;
		case TIFF_LONG:
			fld->set_field_type = TIFF_SETGET_C32_UINT32;
			fld->get_field_type = TIFF_SETGET_C32_UINT32;
			break;
		case TIFF_RATIONAL:
		case TIFF_SRATIONAL:
		case TIFF_FLOAT:
			fld->set_field_type = TIFF_SETGET_C32_FLOAT;
			fld->get_field_type = TIFF_SETGET_C32_FLOAT;
			break;
		case TIFF_SBYTE:
			fld->set_field_type = TIFF_SETGET_C32_SINT8;
			fld->get_field_type = TIFF_SETGET_C32_SINT8;
			break;
		case TIFF_SSHORT:
			fld->set_field_type = TIFF_SETGET_C32_SINT16;
			fld->get_field_type = TIFF_SETGET_C32_SINT16;
			break;
		case TIFF_SLONG:
			fld->set_field_type = TIFF_SETGET_C32_SINT32;
			fld->get_field_type = TIFF_SETGET_C32_SINT32;
			break;
		case TIFF_DOUBLE:
			fld->set_field_type = TIFF_SETGET_C32_DOUBLE;
			fld->get_field_type = TIFF_SETGET_C32_DOUBLE;
			break;
		case TIFF_IFD:
		case TIFF_IFD8:
			fld->set_field_type = TIFF_SETGET_C32_IFD8;
			fld->get_field_type = TIFF_SETGET_C32_IFD8;
			break;
		case TIFF_LONG8:
			fld->set_field_type = TIFF_SETGET_C32_UINT64;
			fld->get_field_type = TIFF_SETGET_C32_UINT64;
			break;
		case TIFF_SLONG8:
			fld->set_field_type = TIFF_SETGET_C32_SINT64;
			fld->get_field_type = TIFF_SETGET_C32_SINT64;
			break;
		default:
			fld->set_field_type = TIFF_SETGET_UNDEFINED;
			fld->get_field_type = TIFF_SETGET_UNDEFINED;
			break;
	}
	fld->field_bit = FIELD_CUSTOM;
	fld->field_oktochange = TRUE;
	fld->field_passcount = TRUE;
	fld->field_name = (char *) _TIFFmalloc(32);
	if (fld->field_name == nullptr) {
		_TIFFfree(fld);
		return nullptr;
	}
	fld->field_subfields = nullptr;

	/* 
	 * note that this name is a special sign to TIFFClose() and
	 * _TIFFSetupFields() to free the field
	 */
	(void) snprintf(fld->field_name, 32, "Tag %d", (int) tag);

	return fld;
}

/****************************************************************************
 *               O B S O L E T E D    I N T E R F A C E S
 *
 * Don't use this stuff in your applications, it may be removed in the future
 * libtiff versions.
 ****************************************************************************/

static TIFFSetGetFieldType
_TIFFSetGetType(TIFFDataType type, short count, unsigned char passcount) {
	if (type == TIFF_ASCII && count == TIFF_VARIABLE && passcount == 0)
		return TIFF_SETGET_ASCII;

	else if (count == 1 && passcount == 0) {
		switch (type) {
			case TIFF_BYTE:
			case TIFF_UNDEFINED:
				return TIFF_SETGET_UINT8;
			case TIFF_ASCII:
				return TIFF_SETGET_ASCII;
			case TIFF_SHORT:
				return TIFF_SETGET_UINT16;
			case TIFF_LONG:
				return TIFF_SETGET_UINT32;
			case TIFF_RATIONAL:
			case TIFF_SRATIONAL:
			case TIFF_FLOAT:
				return TIFF_SETGET_FLOAT;
			case TIFF_SBYTE:
				return TIFF_SETGET_SINT8;
			case TIFF_SSHORT:
				return TIFF_SETGET_SINT16;
			case TIFF_SLONG:
				return TIFF_SETGET_SINT32;
			case TIFF_DOUBLE:
				return TIFF_SETGET_DOUBLE;
			case TIFF_IFD:
			case TIFF_IFD8:
				return TIFF_SETGET_IFD8;
			case TIFF_LONG8:
				return TIFF_SETGET_UINT64;
			case TIFF_SLONG8:
				return TIFF_SETGET_SINT64;
			default:
				return TIFF_SETGET_UNDEFINED;
		}
	} else if (count >= 1 && passcount == 0) {
		switch (type) {
			case TIFF_BYTE:
			case TIFF_UNDEFINED:
				return TIFF_SETGET_C0_UINT8;
			case TIFF_ASCII:
				return TIFF_SETGET_C0_ASCII;
			case TIFF_SHORT:
				return TIFF_SETGET_C0_UINT16;
			case TIFF_LONG:
				return TIFF_SETGET_C0_UINT32;
			case TIFF_RATIONAL:
			case TIFF_SRATIONAL:
			case TIFF_FLOAT:
				return TIFF_SETGET_C0_FLOAT;
			case TIFF_SBYTE:
				return TIFF_SETGET_C0_SINT8;
			case TIFF_SSHORT:
				return TIFF_SETGET_C0_SINT16;
			case TIFF_SLONG:
				return TIFF_SETGET_C0_SINT32;
			case TIFF_DOUBLE:
				return TIFF_SETGET_C0_DOUBLE;
			case TIFF_IFD:
			case TIFF_IFD8:
				return TIFF_SETGET_C0_IFD8;
			case TIFF_LONG8:
				return TIFF_SETGET_C0_UINT64;
			case TIFF_SLONG8:
				return TIFF_SETGET_C0_SINT64;
			default:
				return TIFF_SETGET_UNDEFINED;
		}
	} else if (count == TIFF_VARIABLE && passcount == 1) {
		switch (type) {
			case TIFF_BYTE:
			case TIFF_UNDEFINED:
				return TIFF_SETGET_C16_UINT8;
			case TIFF_ASCII:
				return TIFF_SETGET_C16_ASCII;
			case TIFF_SHORT:
				return TIFF_SETGET_C16_UINT16;
			case TIFF_LONG:
				return TIFF_SETGET_C16_UINT32;
			case TIFF_RATIONAL:
			case TIFF_SRATIONAL:
			case TIFF_FLOAT:
				return TIFF_SETGET_C16_FLOAT;
			case TIFF_SBYTE:
				return TIFF_SETGET_C16_SINT8;
			case TIFF_SSHORT:
				return TIFF_SETGET_C16_SINT16;
			case TIFF_SLONG:
				return TIFF_SETGET_C16_SINT32;
			case TIFF_DOUBLE:
				return TIFF_SETGET_C16_DOUBLE;
			case TIFF_IFD:
			case TIFF_IFD8:
				return TIFF_SETGET_C16_IFD8;
			case TIFF_LONG8:
				return TIFF_SETGET_C16_UINT64;
			case TIFF_SLONG8:
				return TIFF_SETGET_C16_SINT64;
			default:
				return TIFF_SETGET_UNDEFINED;
		}
	} else if (count == TIFF_VARIABLE2 && passcount == 1) {
		switch (type) {
			case TIFF_BYTE:
			case TIFF_UNDEFINED:
				return TIFF_SETGET_C32_UINT8;
			case TIFF_ASCII:
				return TIFF_SETGET_C32_ASCII;
			case TIFF_SHORT:
				return TIFF_SETGET_C32_UINT16;
			case TIFF_LONG:
				return TIFF_SETGET_C32_UINT32;
			case TIFF_RATIONAL:
			case TIFF_SRATIONAL:
			case TIFF_FLOAT:
				return TIFF_SETGET_C32_FLOAT;
			case TIFF_SBYTE:
				return TIFF_SETGET_C32_SINT8;
			case TIFF_SSHORT:
				return TIFF_SETGET_C32_SINT16;
			case TIFF_SLONG:
				return TIFF_SETGET_C32_SINT32;
			case TIFF_DOUBLE:
				return TIFF_SETGET_C32_DOUBLE;
			case TIFF_IFD:
			case TIFF_IFD8:
				return TIFF_SETGET_C32_IFD8;
			case TIFF_LONG8:
				return TIFF_SETGET_C32_UINT64;
			case TIFF_SLONG8:
				return TIFF_SETGET_C32_SINT64;
			default:
				return TIFF_SETGET_UNDEFINED;
		}
	}

	return TIFF_SETGET_UNDEFINED;
}

int
TIFFMergeFieldInfo(TIFF *tif, const TIFFFieldInfo info[], uint32 n) {
	static const char module[] = "TIFFMergeFieldInfo";
	static const char reason[] = "for fields array";
	TIFFField *tp;
	size_t nfields;
	uint32 i;

	if (tif->tif_nfieldscompat > 0) {
		tif->tif_fieldscompat = (TIFFFieldArray *)
				_TIFFCheckRealloc(tif, tif->tif_fieldscompat,
				                  tif->tif_nfieldscompat + 1,
				                  sizeof(TIFFFieldArray), reason);
	} else {
		tif->tif_fieldscompat = (TIFFFieldArray *)
				_TIFFCheckMalloc(tif, 1, sizeof(TIFFFieldArray),
				                 reason);
	}
	if (!tif->tif_fieldscompat) {
		TIFFErrorExt(tif->tif_clientdata, module,
		             "Failed to allocate fields array");
		return -1;
	}
	nfields = tif->tif_nfieldscompat++;

	tif->tif_fieldscompat[nfields].type = tfiatOther;
	tif->tif_fieldscompat[nfields].allocated_size = n;
	tif->tif_fieldscompat[nfields].count = n;
	tif->tif_fieldscompat[nfields].fields =
			(TIFFField *) _TIFFCheckMalloc(tif, n, sizeof(TIFFField),
			                               reason);
	if (!tif->tif_fieldscompat[nfields].fields) {
		TIFFErrorExt(tif->tif_clientdata, module,
		             "Failed to allocate fields array");
		return -1;
	}

	tp = tif->tif_fieldscompat[nfields].fields;
	for (i = 0; i < n; i++) {
		tp->field_tag = info[i].field_tag;
		tp->field_readcount = info[i].field_readcount;
		tp->field_writecount = info[i].field_writecount;
		tp->field_type = info[i].field_type;
		tp->reserved = 0;
		tp->set_field_type =
				_TIFFSetGetType(info[i].field_type,
				                info[i].field_readcount,
				                info[i].field_passcount);
		tp->get_field_type =
				_TIFFSetGetType(info[i].field_type,
				                info[i].field_readcount,
				                info[i].field_passcount);
		tp->field_bit = info[i].field_bit;
		tp->field_oktochange = info[i].field_oktochange;
		tp->field_passcount = info[i].field_passcount;
		tp->field_name = info[i].field_name;
		tp->field_subfields = nullptr;
		tp++;
	}

	if (!_TIFFMergeFields(tif, tif->tif_fieldscompat[nfields].fields, n)) {
		TIFFErrorExt(tif->tif_clientdata, module,
		             "Setting up field info failed");
		return -1;
	}

	return 0;
}

int
_TIFFCheckFieldIsValidForCodec(TIFF *tif, ttag_t tag) {
	/* Filter out non-codec specific tags */
	switch (tag) {
		/* Shared tags */
		case TIFFTAG_PREDICTOR:
			/* JPEG tags */
		case TIFFTAG_JPEGTABLES:
			/* OJPEG tags */
		case TIFFTAG_JPEGIFOFFSET:
		case TIFFTAG_JPEGIFBYTECOUNT:
		case TIFFTAG_JPEGQTABLES:
		case TIFFTAG_JPEGDCTABLES:
		case TIFFTAG_JPEGACTABLES:
		case TIFFTAG_JPEGPROC:
		case TIFFTAG_JPEGRESTARTINTERVAL:
			/* CCITT* */
		case TIFFTAG_BADFAXLINES:
		case TIFFTAG_CLEANFAXDATA:
		case TIFFTAG_CONSECUTIVEBADFAXLINES:
		case TIFFTAG_GROUP3OPTIONS:
		case TIFFTAG_GROUP4OPTIONS:
			break;
		default:
			return 1;
	}
	/* Check if codec specific tags are allowed for the current
	 * compression scheme (codec) */
	switch (tif->tif_dir.td_compression) {
		case COMPRESSION_LZW:
			if (tag == TIFFTAG_PREDICTOR)
				return 1;
			break;
		case COMPRESSION_PACKBITS:
			/* No codec-specific tags */
			break;
		case COMPRESSION_THUNDERSCAN:
			/* No codec-specific tags */
			break;
		case COMPRESSION_NEXT:
			/* No codec-specific tags */
			break;
		case COMPRESSION_JPEG:
			if (tag == TIFFTAG_JPEGTABLES)
				return 1;
			break;
		case COMPRESSION_OJPEG:
			switch (tag) {
				case TIFFTAG_JPEGIFOFFSET:
				case TIFFTAG_JPEGIFBYTECOUNT:
				case TIFFTAG_JPEGQTABLES:
				case TIFFTAG_JPEGDCTABLES:
				case TIFFTAG_JPEGACTABLES:
				case TIFFTAG_JPEGPROC:
				case TIFFTAG_JPEGRESTARTINTERVAL:
					return 1;
			}
			break;
		case COMPRESSION_CCITTRLE:
		case COMPRESSION_CCITTRLEW:
		case COMPRESSION_CCITTFAX3:
		case COMPRESSION_CCITTFAX4:
			switch (tag) {
				case TIFFTAG_BADFAXLINES:
				case TIFFTAG_CLEANFAXDATA:
				case TIFFTAG_CONSECUTIVEBADFAXLINES:
					return 1;
				case TIFFTAG_GROUP3OPTIONS:
					if (tif->tif_dir.td_compression == COMPRESSION_CCITTFAX3)
						return 1;
					break;
				case TIFFTAG_GROUP4OPTIONS:
					if (tif->tif_dir.td_compression == COMPRESSION_CCITTFAX4)
						return 1;
					break;
			}
			break;
		case COMPRESSION_JBIG:
			/* No codec-specific tags */
			break;
		case COMPRESSION_DEFLATE:
		case COMPRESSION_ADOBE_DEFLATE:
			if (tag == TIFFTAG_PREDICTOR)
				return 1;
			break;
		case COMPRESSION_PIXARLOG:
			if (tag == TIFFTAG_PREDICTOR)
				return 1;
			break;
		case COMPRESSION_SGILOG:
		case COMPRESSION_SGILOG24:
			/* No codec-specific tags */
			break;
		case COMPRESSION_LZMA:
			if (tag == TIFFTAG_PREDICTOR)
				return 1;
			break;

	}
	return 0;
}

/* vim: set ts=8 sts=8 sw=8 noet: */

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * fill-column: 78
 * End:
 */
