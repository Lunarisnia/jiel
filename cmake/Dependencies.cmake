include(FetchContent)

find_package(OpenGL REQUIRED)

# Keep dependency configuration here so adding or updating a library does not
# clutter the application targets.
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_GPU OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_GPU OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_VULKAN OFF CACHE BOOL "" FORCE)
set(SDL_VULKAN OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 12.2.0
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL
)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.16
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL
)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
    GIT_SHALLOW TRUE
    SOURCE_SUBDIR cmake
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(fmt SDL3 glad)

# OpenGL 4.1 core is the highest core profile shared by Windows and macOS.
glad_add_library(glad_gl_core_41 STATIC REPRODUCIBLE API gl:core=4.1)
