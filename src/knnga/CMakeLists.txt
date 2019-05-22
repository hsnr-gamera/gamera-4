set(KDTREE_SOURCE knngamodule.cpp)
#TODO check if openmp enabled

add_library(knnga SHARED ${KDTREE_SOURCE})
target_include_directories(knnga PUBLIC ${PROJECT_SOURCE_DIR}/src/eodev)

set_target_properties(
        knnga
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "knnga"
        LINKER_LANGUAGE CXX
)
