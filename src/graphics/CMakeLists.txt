set(MAPLE_GRAPHICS_SOURCES
    ray/ray.cpp
    ray/ray.hpp)

add_library(MapleGraphics ${MAPLE_GRAPHICS_SOURCES})
target_link_libraries(MapleGraphics PRIVATE MapleMathematics)
target_compile_features(MapleGraphics PUBLIC cxx_std_17)
target_include_directories(MapleGraphics PRIVATE ./)

assign_source_group(${MAPLE_GRAPHICS_SOURCES})
