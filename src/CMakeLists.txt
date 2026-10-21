add_library(jiel_engine STATIC
    application.cpp
    debug_geometry.cpp
    debug_renderer.cpp
    file.cpp
    fps_counter.cpp
    game_object.cpp
    mesh_loader.cpp
    time.cpp
    ecs/component.cpp
    ecs/mesh_renderer_component.cpp
    ecs/transform_component.cpp
    graphics/graphics.cpp
    graphics/material.cpp
    graphics/mesh.cpp
    graphics/shader.cpp
    primitives/plane.cpp
    primitives/triangle.cpp
    ${PROJECT_SOURCE_DIR}/include/ecs/component.hpp
    ${PROJECT_SOURCE_DIR}/include/ecs/mesh_renderer_component.hpp
    ${PROJECT_SOURCE_DIR}/include/ecs/transform_component.hpp
    ${PROJECT_SOURCE_DIR}/include/game_object.hpp
    ${PROJECT_SOURCE_DIR}/include/debug_renderer.hpp
    ${PROJECT_SOURCE_DIR}/include/primitives/plane.hpp
    ${PROJECT_SOURCE_DIR}/include/primitives/triangle.hpp
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

target_link_libraries(jiel_engine PUBLIC assimp::assimp jiel::math)

target_link_libraries(jiel_engine
    PRIVATE
        fmt::fmt
        glad_gl_core_41
        imgui
        SDL3::SDL3
)

jiel_enable_warnings(jiel_engine)
