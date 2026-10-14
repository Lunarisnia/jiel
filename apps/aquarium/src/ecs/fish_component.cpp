#include "ecs/fish_component.hpp"
#include "ecs/mesh_renderer_component.hpp"
#include "game_object.hpp"
#include "time.hpp"

FishComponent::FishComponent() : Component("FishComponent") {}

void FishComponent::Init() {
    gameObject->transform->scale *= 0.3f;
    meshRenderer = gameObject->GetComponent<MeshRendererComponent>();
}

void FishComponent::Update() {
    meshRenderer->material->shader->SetFloatUniform("time", static_cast<float>(Time::GetTime()));
}
