# Makes it easier to configure the include directories in the subdirectories
set(ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Sub-projects to improve compile times and modularity
# Projects are listed from lease dependencies to most dependencies
add_subdirectory(thirdparty)    # Depends on: nothing
add_subdirectory(mathematics)   # Depends on: nothing
add_subdirectory(graphics)      # Depends on: mathematics, thirdparty

# Main project - the Maple renderer
set(MAPLE_SOURCES
    main.cpp)

add_executable(Maple ${MAPLE_SOURCES})
target_link_libraries(Maple PRIVATE MapleMathematics MapleGraphics MapleThirdparty)
target_compile_features(Maple PUBLIC cxx_std_17)
target_include_directories(Maple PRIVATE ${ROOT_SOURCE_DIR})

assign_source_group(${MAPLE_SOURCES})
