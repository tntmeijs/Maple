set(MAPLE_GRAPHICS_SOURCES
    ray/ray.cpp
    ray/ray.hpp
    shading/sky_gradient.hpp
    intersection/hitable_object.hpp
    intersection/sphere.cpp
    intersection/sphere.hpp
    intersection/hit_list.cpp
    intersection/hit_list.hpp)

add_library(MapleGraphics ${MAPLE_GRAPHICS_SOURCES})
target_compile_features(MapleGraphics PUBLIC cxx_std_17)
target_include_directories(MapleGraphics PRIVATE
    ${ROOT_SOURCE_DIR}              # Include the graphics root directory
    ${ROOT_SOURCE_DIR}/graphics)    # Include the project root directory

assign_source_group(${MAPLE_GRAPHICS_SOURCES})
