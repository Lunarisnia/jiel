#include "application.hpp"
#include "SDL3/SDL_video.h"
#include "file.hpp"
#include "fmt/format.h"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "mesh_loader.hpp"
#include "primitives/plane.hpp"
#include "time.hpp"

#include <SDL3/SDL.h>
#include <expected>
#include <fmt/base.h>
#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <memory>
#include <string>

Application::Application() = default;

constexpr WindowSize WINDOW_SIZE = {
    .Width = 1028,
    .Height = 720,
};

std::unique_ptr<Shader> basicShader;
std::unique_ptr<Mesh> plane;
std::unique_ptr<Mesh> head;

void setupDrawTriangle() {
    // TODO: find out why does this not properly render in renderdoc
    std::expected<Mesh, std::string> loadedHead =
        MeshLoader::LoadOBJ("apps/sandbox/models/obj/african_head/african_head.obj");
    if (!loadedHead.has_value()) {
        fmt::println("couldn't load model: ", loadedHead.error());
        return;
    }
    head = std::make_unique<Mesh>(loadedHead.value());
    plane = std::make_unique<Mesh>(primitive::CreatePlane());

    const std::string vertexShaderSource = File::LoadFile("apps/sandbox/shaders/vertex.vert");
    const std::string fragmentShaderSource = File::LoadFile("apps/sandbox/shaders/fragment.frag");

    basicShader = std::make_unique<Shader>();
    basicShader->Add(vertexShaderSource, GL_VERTEX_SHADER);
    basicShader->Add(fragmentShaderSource, GL_FRAGMENT_SHADER);

    basicShader->Compile();
}

void drawTriangle() {
    basicShader->Use();

    // plane->Draw();
    head->Draw();
}

// TODO: should this be here?
double prevTick;
double fpsCooldown = 0.1f;
void fpsCounter(SDL_Window* window, Time time) {
    double currentTick = time.GetTime();

    double elapsedTick = currentTick - prevTick;
    prevTick = currentTick;

    fpsCooldown -= elapsedTick;
    if (fpsCooldown < 0.0f && elapsedTick > 0.0f) {
        double fps = 1.0f / elapsedTick;

        SDL_SetWindowTitle(window, fmt::format("FPS: {}", fps).c_str());
        fpsCooldown = 0.1f;
    }
}

void Application::Init() {
    createWindow();
    createOpenGLContext();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 410 core");
    imguiInitialized = true;

    setupDrawTriangle();

    Time time{};
    prevTick = time.GetTime();
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        int width = 0;
        int height = 0;
        SDL_GetWindowSizeInPixels(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.075f, 0.075F, 0.11F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        drawTriangle();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        fpsCounter(window, time);

        SDL_GL_SwapWindow(window);
    }
}

void Application::createWindow() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fmt::println("Failed to initialize video: {}", SDL_GetError());
        return;
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

    window =
        SDL_CreateWindow("jiel", WINDOW_SIZE.Width, WINDOW_SIZE.Height,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (window == nullptr) {
        fmt::println("Could not create a window: {}", SDL_GetError());
        SDL_Quit();
        return;
    }
}

void Application::createOpenGLContext() {
    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        fmt::println("Could not create an OpenGL context: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    if (gladLoadGL(SDL_GL_GetProcAddress) == 0) {
        fmt::println("Could not load OpenGL: {}", SDL_GetError());
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_GL_SetSwapInterval(1);
    fmt::print("OpenGL {}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

Application::~Application() {
    if (imguiInitialized) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
