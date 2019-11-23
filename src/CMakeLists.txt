# Sub-projects to improve compile times and modularity
# Projects are listed from lease dependencies to most dependencies
add_subdirectory(mathematics)   # Depends on: nothing
add_subdirectory(graphics)      # Depends on: mathematics

# Main project - the Maple renderer
set(MAPLE_SOURCES
    main.cpp)

add_executable(Maple ${MAPLE_SOURCES})
target_link_libraries(Maple PRIVATE MapleMathematics)
target_link_libraries(Maple PRIVATE MapleGraphics)
target_compile_features(Maple PUBLIC cxx_std_17)
target_include_directories(Maple PRIVATE ./)

assign_source_group(${MAPLE_SOURCES})
