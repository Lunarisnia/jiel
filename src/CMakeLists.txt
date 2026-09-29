add_library(jiel_engine
    application.cpp
    graphics/graphics.cpp
)

add_library(jiel::engine ALIAS jiel_engine)

target_compile_features(jiel_engine PUBLIC cxx_std_23)

target_include_directories(jiel_engine
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(jiel_engine
    PRIVATE
        fmt::fmt
        glad_gl_core_41
        SDL3::SDL3
)

jiel_enable_warnings(jiel_engine)
