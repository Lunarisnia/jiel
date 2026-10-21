#include "SDL3/SDL_events.h"
#include "application.hpp"
#include "debug_inspector.hpp"
#include "debug_renderer.hpp"
#include "ecs/fish_component.hpp"
#include "ecs/food_component.hpp"
#include "ecs/mesh_renderer_component.hpp"
#include "ecs/triggerbox_component.hpp"
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
#include <glad/gl.h>
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

    auto debugRenderer = DebugRenderer::Create();
    if (!debugRenderer) {
        fmt::println(stderr, "Could not create debug renderer: {}", debugRenderer.error());
        return 1;
    }

    std::shared_ptr<World> world = std::make_shared<World>();

    auto shader = std::make_shared<Shader>();
    auto shaderVertex =
        shader->Add(File::LoadFile("apps/aquarium/shaders/aquarium.vert"), GL_VERTEX_SHADER);
    auto shaderFragment =
        shaderVertex
            ? shader->Add(File::LoadFile("apps/aquarium/shaders/aquarium.frag"), GL_FRAGMENT_SHADER)
            : shaderVertex;
    auto shaderLink = shaderFragment ? shader->Compile() : shaderFragment;
    if (!shaderLink) {
        fmt::println(stderr, "Could not create aquarium shader: {}", shaderLink.error());
        return 1;
    }

    auto material = std::make_shared<Material>(shader);
    auto triangle = std::make_shared<Mesh>(primitive::CreateTriangle());
    auto meshRenderer = std::make_shared<MeshRendererComponent>(triangle, material);
    auto fishComponent = std::make_shared<FishComponent>();

    auto fish = std::make_shared<GameObject>();
    fish->AddComponent(meshRenderer);
    fish->AddComponent(fishComponent);
    world->AddGameObject(fish);

    // TODO: Refactor plan
    // 1. Split Update & Render tick, so that Update is exclusively for simulation and render is for
    // rendering
    // 2. Create a RenderableComponent inheriting from Component
    // 3. Refactor gameobject to fit this new pattern
    // 4. Add api to attach camera to meshRenderer
    // 5. Have mesh renderer be responsible of its own draw call (setting MVP matrix)
    // TODO: do camera
    // TODO: trigger box is still shitty due to coordinate issue
    auto foodShader = std::make_shared<Shader>();
    auto foodVertex =
        foodShader->Add(File::LoadFile("apps/aquarium/shaders/aquarium.vert"), GL_VERTEX_SHADER);
    auto foodFragment = foodVertex
                            ? foodShader->Add(File::LoadFile("assets/shaders/common/solid.frag"),
                                              GL_FRAGMENT_SHADER)
                            : foodVertex;
    auto foodLink = foodFragment ? foodShader->Compile() : foodFragment;
    if (!foodLink) {
        fmt::println(stderr, "Could not create food shader: {}", foodLink.error());
        return 1;
    }
    foodShader->SetVec3Uniform("color", math::Vec3{1.0F, 1.0F, 0.0F});
    auto foodMeshMaterial = std::make_shared<Material>(foodShader);
    auto foodMesh = std::make_shared<Mesh>(primitive::CreatePlane());
    auto foodMeshRenderer = std::make_shared<MeshRendererComponent>(foodMesh, foodMeshMaterial);
    auto foodComponent = std::make_shared<FoodComponent>();
    auto triggerBox = std::make_shared<TriggerBoxComponent>(world, *debugRenderer);

    auto food = std::make_shared<GameObject>();
    food->transform->position.z = 0.0f;
    food->AddComponent(foodMeshRenderer);
    food->AddComponent(foodComponent);
    food->AddComponent(triggerBox);
    world->AddGameObject(food);

    world->Init();
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

        world->Update();

        debugRenderer->Render();

        app.EndFrame();
    }
}
