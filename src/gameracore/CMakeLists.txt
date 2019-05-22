set(KDTREE_SOURCE dimobject.cpp
        floatpointobject.cpp
        gameramodule.cpp
        imagedataobject.cpp
        imageinfoobject.cpp
        imageobject.cpp
        iteratorobject.cpp
        pointobject.cpp
        rectobject.cpp
        regionmapobject.cpp
        regionobject.cpp
        rgbpixelobject.cpp
        sizeobject.cpp)

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${GAMERA_SOURCE})

add_library(gameracore SHARED ${KDTREE_SOURCE})

set_target_properties(
        gameracore
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "gameracore"
        LINKER_LANGUAGE CXX
)
