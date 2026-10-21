add_executable(debug_geometry_test
    debug_geometry_test.cpp
    ${PROJECT_SOURCE_DIR}/src/debug_geometry.cpp
)

target_include_directories(debug_geometry_test PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

target_compile_features(debug_geometry_test PRIVATE cxx_std_23)
jiel_enable_warnings(debug_geometry_test)

add_test(NAME debug_geometry COMMAND debug_geometry_test)

add_executable(look_at_test look_at_test.cpp)
target_link_libraries(look_at_test PRIVATE jiel::math)
jiel_enable_warnings(look_at_test)
add_test(NAME look_at COMMAND look_at_test)
