# Sub-projects to improve compile times and modularity
add_subdirectory(mathematics)

# Main project - the Maple renderer
set(MAPLE_RENDERER_SOURCES
    main.cpp)

add_executable(MapleRenderer ${MAPLE_RENDERER_SOURCES})
target_link_libraries(MapleRenderer PRIVATE MapleMathematics)
target_compile_features(MapleRenderer PUBLIC cxx_std_17)
target_include_directories(MapleRenderer PRIVATE ./)

assign_source_group(${MAPLE_RENDERER_SOURCES})
