set(KDTREE_SOURCE knncoremodule.cpp)

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${GAMERA_SOURCE})

add_library(knncore SHARED ${KDTREE_SOURCE})

set_target_properties(
        knncore
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "knncore"
        LINKER_LANGUAGE CXX
)
