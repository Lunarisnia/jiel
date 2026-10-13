#include "ecs/fish_component.hpp"
#include "ecs/transform_component.hpp"
#include "game_object.hpp"
#include <cmath>
#include <memory>

FishComponent::FishComponent() : Component("FishComponent") {}

void FishComponent::Init() {}

void FishComponent::Update() {
    std::shared_ptr<TransformComponent> transform = gameObject->GetComponent<TransformComponent>();
    transform->position.x = std::sin(time.GetTime());
}
