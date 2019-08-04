set(TIFF_SOURCE
        fax3sm_winnt.cpp
        tif_aux.cpp
        tif_close.cpp
        ${GAMERA_SOURCE}/plugins/tiff_support.hpp
        tif_codec.cpp
        tif_compress.cpp
        tif_dir.cpp
        tif_dirinfo.cpp
        tif_dirread.cpp
        tif_dirwrite.cpp
        tif_zip.cpp
        tif_write.cpp
        tif_warning.cpp
        tif_version.cpp
        tif_unix.cpp
        tif_tile.cpp
        tif_thunder.cpp
        tif_swab.cpp
        tif_strip.cpp
        tif_read.cpp
        tif_print.cpp
        tif_predict.cpp
        tif_packbits.cpp
        )

add_library(tiff_support SHARED ${TIFF_SOURCE})
add_definitions(-DCPP_COMPILE)

set_target_properties(
        tiff_support
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "tiff_support"
        LINKER_LANGUAGE CXX
)
