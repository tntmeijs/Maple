set(MAPLE_GRAPHICS_SOURCES
    ray/ray.cpp
    ray/ray.hpp)

add_library(MapleGraphics ${MAPLE_GRAPHICS_SOURCES})
target_link_libraries(MapleGraphics PRIVATE MapleMathematics)
target_compile_features(MapleGraphics PUBLIC cxx_std_17)
target_include_directories(MapleGraphics PRIVATE
    ${ROOT_SOURCE_DIR}              # Include the graphics root directory
    ${ROOT_SOURCE_DIR}/graphics)    # Include the project root directory

assign_source_group(${MAPLE_GRAPHICS_SOURCES})
