#include "SDL3/SDL_events.h"
#include "application.hpp"
#include "ecs/mesh_renderer.hpp"
#include "file.hpp"
#include "fmt/base.h"
#include "game_object.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "primitives/triangle.hpp"
#include "time.hpp"
#include <memory>

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

    auto shader = std::make_shared<Shader>();
    shader->Add(File::LoadFile("apps/aquarium/shaders/aquarium.vert"), GL_VERTEX_SHADER);
    shader->Add(File::LoadFile("apps/aquarium/shaders/aquarium.frag"), GL_FRAGMENT_SHADER);
    shader->Compile();

    auto material = std::make_shared<Material>(shader);
    auto triangle = std::make_shared<Mesh>(primitive::CreateTriangle());
    auto meshRenderer = std::make_shared<MeshRenderer>(triangle, material);

    GameObject fish{};
    fish.AddComponent(meshRenderer);

    Time time{};
    bool running = true;
    while (running) {
        SDL_Event event;
        while (app.PollEvent(event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        app.BeginFrame();
        shader->SetFloatUniform("time", static_cast<float>(time.GetTime()));
        fish.Update();

        app.EndFrame();
    }
}
