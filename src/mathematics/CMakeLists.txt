set(MAPLE_MATHEMATICS_SOURCES
    vector/vector3.cpp
    vector/vector3.hpp
    utility/point_on_unit_sphere.hpp
    utility/constants.hpp
    utility/literals.hpp
    utility/indexing.hpp
    utility/tools.hpp)

add_library(MapleMathematics ${MAPLE_MATHEMATICS_SOURCES})
target_compile_features(MapleMathematics PUBLIC cxx_std_17)
target_include_directories(MapleMathematics PRIVATE ${ROOT_SOURCE_DIR}/mathematics)

assign_source_group(${MAPLE_MATHEMATICS_SOURCES})
