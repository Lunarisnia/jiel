#include <cstdlib>

#include <fmt/base.h>
#include <glad/gl.h>
#include <SDL3/SDL.h>

namespace {

constexpr int window_width = 1280;
constexpr int window_height = 720;

int fail(const char* message)
{
    fmt::print(stderr, "{}: {}\n", message, SDL_GetError());
    return EXIT_FAILURE;
}

} // namespace

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return fail("Could not initialize SDL");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int context_flags = 0;
#ifdef __APPLE__
    context_flags |= SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
#endif
#ifndef NDEBUG
    context_flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);

    SDL_Window* window = SDL_CreateWindow(
        "jiel", window_width, window_height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (window == nullptr) {
        SDL_Quit();
        return fail("Could not create a window");
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return fail("Could not create an OpenGL context");
    }

    if (gladLoadGL(SDL_GL_GetProcAddress) == 0) {
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return fail("Could not load OpenGL");
    }

    SDL_GL_SetSwapInterval(1);
    fmt::print("OpenGL {}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        int width = 0;
        int height = 0;
        SDL_GetWindowSizeInPixels(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.055F, 0.075F, 0.11F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
