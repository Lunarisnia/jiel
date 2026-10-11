#include "SDL3/SDL_events.h"
#include "application.hpp"
#include "file.hpp"
#include "fmt/base.h"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "primitives/triangle.hpp"

int main() {
    ApplicationConfig appConfig{
        .title = "The Aquarium",
        .width = 800,
        .height = 600,
    };
    Application app{appConfig};
    if (!app.IsValid()) {
        fmt::println("Failed to initiate app");
        return 1;
    }

    Shader shader{};
    shader.Add(File::LoadFile("assets/shaders/common/basic.vert"), GL_VERTEX_SHADER);
    shader.Add(File::LoadFile("assets/shaders/common/basic.frag"), GL_FRAGMENT_SHADER);
    shader.Compile();

    Mesh triangle = primitive::CreateTriangle();

    bool running = true;
    while (running) {
        SDL_Event event;
        while (app.PollEvent(event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        app.BeginFrame();
        shader.Use();
        triangle.Draw();

        app.EndFrame();
    }
}
