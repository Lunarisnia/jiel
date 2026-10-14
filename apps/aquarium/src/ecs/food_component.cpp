#include "ecs/food_component.hpp"
#include "game_object.hpp"

FoodComponent::FoodComponent() : Component("FoodComponent") {}

void FoodComponent::Init() {
    gameObject->transform->position.y = 0.5f;
    gameObject->transform->scale *= 0.1f;
}

void FoodComponent::Update() {}
