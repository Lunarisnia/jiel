add_executable(aquarium
    main.cpp
    src/game_object.cpp
    src/ecs/component.cpp
    src/ecs/mesh_renderer.cpp
    include/game_object.hpp
    include/ecs/component.hpp
    include/ecs/mesh_renderer.hpp
    include/ecs/transform.hpp
)

target_include_directories(aquarium
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(aquarium
    PRIVATE
        fmt::fmt
        glad_gl_core_41
        imgui
        jiel::engine
        OpenGL::GL
        SDL3::SDL3
)

if(APPLE)
    target_compile_definitions(aquarium PRIVATE GL_SILENCE_DEPRECATION)
endif()

# A shared SDL build needs its DLL beside the executable on Windows.
if(WIN32)
    add_custom_command(TARGET aquarium POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "$<TARGET_FILE:SDL3::SDL3>"
                "$<TARGET_FILE_DIR:aquarium>"
        VERBATIM
    )
endif()

jiel_enable_warnings(aquarium)
