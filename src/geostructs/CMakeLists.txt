
set(KDTREE_SOURCE kdtreemodule.cpp
            kdtree.cpp)

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${GAMERA_SOURCE})
add_library(kdtree SHARED ${KDTREE_SOURCE})
message(${GAMERA_SOURCE})
set_target_properties(
        kdtree
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "kdtree"
        LINKER_LANGUAGE CXX
)
