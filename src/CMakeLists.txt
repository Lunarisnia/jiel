add_library(jiel_engine
    application.cpp
    file.cpp
    graphics/graphics.cpp
    graphics/mesh.cpp
)

add_library(jiel::engine ALIAS jiel_engine)

add_library(jiel_math INTERFACE)
add_library(jiel::math ALIAS jiel_math)

target_compile_features(jiel_engine PUBLIC cxx_std_23)

target_compile_features(jiel_math INTERFACE cxx_std_23)

target_include_directories(jiel_math
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_include_directories(jiel_engine
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(jiel_engine PUBLIC jiel::math)

target_link_libraries(jiel_engine
    PRIVATE
        fmt::fmt
        glad_gl_core_41
        SDL3::SDL3
)

jiel_enable_warnings(jiel_engine)
