add_executable(jiel main.cpp)

target_link_libraries(jiel
    PRIVATE
        fmt::fmt
        glad_gl_core_41
        jiel::engine
        OpenGL::GL
        SDL3::SDL3
)

if(APPLE)
    target_compile_definitions(jiel PRIVATE GL_SILENCE_DEPRECATION)
endif()

# A shared SDL build needs its DLL beside the executable on Windows.
if(WIN32)
    add_custom_command(TARGET jiel POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "$<TARGET_FILE:SDL3::SDL3>"
                "$<TARGET_FILE_DIR:jiel>"
        VERBATIM
    )
endif()

jiel_enable_warnings(jiel)
