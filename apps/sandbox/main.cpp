#include "application.hpp"
#include "file.hpp"
#include "fps_counter.hpp"
#include "graphics/shader.hpp"
#include "mesh_loader.hpp"
#include "time.hpp"

#include <SDL3/SDL.h>
#include <cstdlib>
#include <fmt/base.h>
#include <fmt/format.h>
#include <glad/gl.h>
#include <imgui.h>
#include <string>

int main() {
    Application app({
        .title = "jiel sandbox",
        .width = 1028,
        .height = 720,
    });
    if (!app.IsValid()) {
        return EXIT_FAILURE;
    }

    auto head = MeshLoader::LoadOBJ("apps/sandbox/models/obj/african_head/african_head.obj");
    if (!head) {
        fmt::println(stderr, "Could not load model: {}", head.error());
        return EXIT_FAILURE;
    }

    Shader shader{};
    shader.Add(File::LoadFile("assets/shaders/common/basic.vert"), GL_VERTEX_SHADER);
    shader.Add(File::LoadFile("assets/shaders/common/basic.frag"), GL_FRAGMENT_SHADER);
    shader.Compile();

    FpsCounter fpsCounter{};
    bool running = true;

    while (running) {
        SDL_Event event{};
        while (app.PollEvent(event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        app.BeginFrame();

        shader.Use();
        head->Draw();
        ImGui::ShowDemoWindow();

        fpsCounter.Update(Time::GetTime());
        if (fpsCounter.WasUpdated()) {
            SDL_SetWindowTitle(
                app.GetWindow(), fmt::format("FPS: {:.1f}", fpsCounter.GetFps()).c_str());
        }

        app.EndFrame();
    }

    return EXIT_SUCCESS;
}
