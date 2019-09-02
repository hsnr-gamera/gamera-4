set(KDTREE_SOURCE kdtreemodule.cpp
            kdtree.cpp)

add_library(kdtree SHARED ${KDTREE_SOURCE})

set_target_properties(
        kdtree
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "kdtree"
        LINKER_LANGUAGE CXX
)
