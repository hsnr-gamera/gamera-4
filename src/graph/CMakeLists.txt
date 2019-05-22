set(KDTREE_SOURCE graphmodule/graphmodule.cpp
            graphmodule/edgeobject.cpp
        graphmodule/graphobject_algorithm.cpp
        graphmodule/graphobject.cpp
        graphmodule/nodeobject.cpp
        graphmodule/partitions.cpp)

add_library(graph SHARED ${KDTREE_SOURCE})
target_include_directories(graph PUBLIC .)
target_include_directories(graph PUBLIC ${GAMERA_SOURCE}/graph)

set_target_properties(
        graph
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "graph"
        LINKER_LANGUAGE CXX
)
