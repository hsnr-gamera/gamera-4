#
# This file has been taken from wxpython (see the file
# wx/tools/img2py.py in the wxpython source distribution)
#
# Copyright (c) 1998 Julian Smart, Robert Roebling et al
#
# This program may be freely used, copied and distributed under
# the terms of the wxWindows Library Licence, Version 3. See
# the file "copyright" of the wxpython distribution from
# http://wxpython.org/ for details.
#
"""
img2py.py  --  Convert an image to PNG format and embed it in a Python
               module with appropriate code so it can be loaded into
               a program at runtime.  The benefit is that since it is
               Python source code it can be delivered as a .pyc or
               'compiled' into the program using freeze, py2exe, etc.

Usage:

    img2py.py [options] image_file python_file

Options:

    -m <#rrggbb>   If the original image has a mask or transparency defined
                   it will be used by default.  You can use this option to
                   override the default or provide a new mask by specifying
                   a colour in the image to mark as transparent.

    -n <name>      Normally generic names (getBitmap, etc.) are used for the
                   image access functions.  If you use this option you can
                   specify a name that should be used to customize the access
                   fucntions, (getNameBitmap, etc.)

    -a             This flag specifies that the python_file should be appended
                   to instead of overwritten.  This in combination with -n will
                   allow you to put multiple images in one Python source file.

    -u             Don't use compression.  Leaves the data uncompressed.

    -i             Also output a function to return the image as a wxIcon.

"""



import sys, os, glob, getopt, tempfile, string
import pickle, io, zlib
import img2img
try:
    import wx
except Exception:
    from wxPython import wx


def crunch_data(data, compressed):
    # compress it?
    if compressed:
        data = zlib.compress(data, 9)

    # convert to a printable format, so it can be in a Python source file
    data = repr(data)

    # This next bit is borrowed from PIL.  It is used to wrap the text intelligently.
    fp = io.StringIO()
    data = data + " "  # buffer for the +1 test
    c = i = 0
    word = ""
    octdigits = "01234567"
    hexdigits = "0123456789abcdef"
    while i < len(data):
        if data[i] != "\\":
            word = data[i]
            i = i + 1
        else:
            if data[i+1] in octdigits:
                for n in range(2, 5):
                    if data[i+n] not in octdigits:
                        break
                word = data[i:i+n]
                i = i + n
            elif data[i+1] == 'x':
                for n in range(2, 5):
                    if data[i+n] not in hexdigits:
                        break
                word = data[i:i+n]
                i = i + n
            else:
                word = data[i:i+2]
                i = i + 2

        l = len(word)
        if c + l >= 78-1:
            fp.write("\\\n")
            c = 0
        fp.write(word)
        c = c + l

    # return the formatted compressed data
    return fp.getvalue()



def main(args):
    if not args or ("-h" in args):
        print(__doc__)
        return

    append = 0
    compressed = 1
    maskClr = None
    imgName = ""
    icon = 0

    try:
        opts, fileArgs = getopt.getopt(args, "auin:m:")
    except getopt.GetoptError:
        print(__doc__)
        return

    for opt, val in opts:
        if opt == "-a":
            append = 1
        elif opt == "-u":
            compressed = 0
        elif opt == "-n":
            imgName = val
        elif opt == "-m":
            maskClr = val
        elif opt == "-i":
            icon = 1

    if len(fileArgs) != 2:
        print(__doc__)
        return

    image_file, python_file = fileArgs

    # convert the image file to a temporary file
    tfname = tempfile.mktemp()
    ok, msg = img2img.convert(image_file, maskClr, None, tfname, wx.BITMAP_TYPE_PNG, ".png")
    if not ok:
        print(msg)
        return

    data = open(tfname, "rb").read()
    data = crunch_data(data, compressed)
    os.unlink(tfname)

    if append:
        out = open(python_file, "a")
    else:
        out = open(python_file, "w")

    out.write("#" + "-" * 70 + "\n")
    if not append:
        out.write("# This file was generated by %s\n#\n" % sys.argv[0])
        out.write("try:\n")
        out.write("   from gamera.gui import compat_wx\n")
        out.write("   wxImageFromStream = compat_wx.create_image_from_stream\n")
        out.write("   wxBitmapFromImage = compat_wx.create_bitmap_from_image\n")
        out.write("except Exception:\n")
        out.write("   from wxPython.wx import wxImageFromStream, wxBitmapFromImage\n")
        if compressed:
            out.write("import cStringIO, zlib\n\n\n")
        else:
            out.write("import cStringIO\n\n\n")

    if compressed:
        out.write("def get%sData():\n"
                  "    return zlib.decompress(\n%s)\n\n"
                  % (imgName, data))
    else:
        out.write("def get%sData():\n"
                  "    return \\\n%s\n\n"
                  % (imgName, data))


    out.write("def get%sBitmap():\n"
              "    return wxBitmapFromImage(get%sImage())\n\n"
              "def get%sImage():\n"
              "    stream = cStringIO.StringIO(get%sData())\n"
              "    return wxImageFromStream(stream)\n\n"
              % tuple([imgName] * 4))
    if icon:
        out.write("def get%sIcon():\n"
                  "    icon = wxEmptyIcon()\n"
                  "    icon.CopyFromBitmap(get%sBitmap())\n"
                  "    return icon\n\n"
                  % tuple([imgName] * 2))


    if imgName:
        n_msg = ' using "%s"' % imgName
    else:
        n_msg = ""
    if maskClr:
        m_msg = " with mask %s" % maskClr
    else:
        m_msg = ""
    print("Embedded %s%s into %s%s" % (image_file, n_msg, python_file, m_msg))

if __name__ == "__main__":
    main(sys.argv[1:])

