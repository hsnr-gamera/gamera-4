set(KDTREE_SOURCE knncoremodule.cpp)

add_library(knncore SHARED ${KDTREE_SOURCE})

set_target_properties(
        knncore
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "knncore"
        LINKER_LANGUAGE CXX
)
