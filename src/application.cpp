#include "application.hpp"

#include <SDL3/SDL.h>
#include <fmt/base.h>
#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

Application::Application(const ApplicationConfig& config) {
    if (!createWindow(config) || !createOpenGLContext()) {
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    if (!ImGui_ImplSDL3_InitForOpenGL(window, context)) {
        fmt::println(stderr, "Could not initialize ImGui SDL backend");
        ImGui::DestroyContext();
        return;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 410 core")) {
        fmt::println(stderr, "Could not initialize ImGui OpenGL backend");
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        return;
    }

    imguiInitialized = true;
    initialized = true;
}

bool Application::IsValid() const {
    return initialized;
}

SDL_Window* Application::GetWindow() const {
    return window;
}

bool Application::PollEvent(SDL_Event& event) {
    if (!SDL_PollEvent(&event)) {
        return false;
    }

    ImGui_ImplSDL3_ProcessEvent(&event);
    return true;
}

void Application::BeginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    int width = 0;
    int height = 0;
    SDL_GetWindowSizeInPixels(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.075F, 0.075F, 0.11F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Application::EndFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}

bool Application::createWindow(const ApplicationConfig& config) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fmt::println(stderr, "Failed to initialize video: {}", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int contextFlags = 0;
#ifdef __APPLE__
    contextFlags |= SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
#endif
#ifndef NDEBUG
    contextFlags |= SDL_GL_CONTEXT_DEBUG_FLAG;
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, contextFlags);

    window = SDL_CreateWindow(config.title.c_str(), config.width, config.height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                  SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (window == nullptr) {
        fmt::println(stderr, "Could not create a window: {}", SDL_GetError());
        return false;
    }

    return true;
}

bool Application::createOpenGLContext() {
    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        fmt::println(stderr, "Could not create an OpenGL context: {}", SDL_GetError());
        return false;
    }

    if (gladLoadGL(SDL_GL_GetProcAddress) == 0) {
        fmt::println(stderr, "Could not load OpenGL: {}", SDL_GetError());
        return false;
    }

    SDL_GL_SetSwapInterval(1);
    fmt::println("OpenGL {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    return true;
}

Application::~Application() {
    if (imguiInitialized) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
    if (context != nullptr) {
        SDL_GL_DestroyContext(context);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
