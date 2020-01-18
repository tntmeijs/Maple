set(MAPLE_THIRDPARTY_SOURCES
    stb/stb_image.h
    stb_header_only_definitions.cpp)

add_library(MapleThirdparty ${MAPLE_THIRDPARTY_SOURCES})
target_compile_features(MapleThirdparty PUBLIC cxx_std_17)
target_include_directories(MapleThirdparty PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/stb)

assign_source_group(${MAPLE_THIRDPARTY_SOURCES})
