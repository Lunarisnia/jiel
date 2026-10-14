#include "SDL3/SDL_events.h"
#include "application.hpp"
#include "debug_inspector.hpp"
#include "ecs/fish_component.hpp"
#include "ecs/food_component.hpp"
#include "ecs/mesh_renderer_component.hpp"
#include "file.hpp"
#include "fmt/base.h"
#include "game_object.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "math/vec3.hpp"
#include "primitives/plane.hpp"
#include "primitives/triangle.hpp"
#include "world.hpp"
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

    World world{};

    auto shader = std::make_shared<Shader>();
    shader->Add(File::LoadFile("apps/aquarium/shaders/aquarium.vert"), GL_VERTEX_SHADER);
    shader->Add(File::LoadFile("apps/aquarium/shaders/aquarium.frag"), GL_FRAGMENT_SHADER);
    shader->Compile();

    auto material = std::make_shared<Material>(shader);
    auto triangle = std::make_shared<Mesh>(primitive::CreateTriangle());
    auto meshRenderer = std::make_shared<MeshRendererComponent>(triangle, material);
    auto fishComponent = std::make_shared<FishComponent>();

    auto fish = std::make_shared<GameObject>();
    fish->AddComponent(meshRenderer);
    fish->AddComponent(fishComponent);
    world.AddGameObject(fish);

    // TODO: handle draw order because zcoord does not seem to work?
    // TODO: do the trigger box
    auto foodShader = std::make_shared<Shader>();
    foodShader->Add(File::LoadFile("apps/aquarium/shaders/aquarium.vert"), GL_VERTEX_SHADER);
    foodShader->Add(File::LoadFile("assets/shaders/common/solid.frag"), GL_FRAGMENT_SHADER);
    foodShader->Compile();
    foodShader->SetVec3Uniform("color", math::Vec3{1.0F, 1.0F, 0.0F});
    auto foodMeshMaterial = std::make_shared<Material>(foodShader);
    auto foodMesh = std::make_shared<Mesh>(primitive::CreatePlane());
    auto foodMeshRenderer = std::make_shared<MeshRendererComponent>(foodMesh, foodMeshMaterial);
    auto foodComponent = std::make_shared<FoodComponent>();

    auto food = std::make_shared<GameObject>();
    food->transform->position.z = -1.0f;
    food->AddComponent(foodMeshRenderer);
    food->AddComponent(foodComponent);
    world.AddGameObject(food);

    world.Init();
    bool running = true;
    while (running) {
        SDL_Event event;
        while (app.PollEvent(event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        app.BeginFrame();
        DebugInspector::Draw(fish.get());

        world.Update();

        app.EndFrame();
    }
}
