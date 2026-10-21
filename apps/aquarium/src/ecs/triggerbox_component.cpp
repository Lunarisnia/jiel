#include "ecs/triggerbox_component.hpp"
#include "fmt/base.h"
#include "math/vec3.hpp"
#include "world.hpp"
#include <memory>

TriggerBoxComponent::TriggerBoxComponent(std::shared_ptr<World> world)
    : Component("TriggerBoxComponent") {
    this->world = world;
}

void TriggerBoxComponent::Init() {}

void TriggerBoxComponent::Update() {
    math::Vec3 topLeft(gameObject->transform->position.x, gameObject->transform->position.y, 0.0f);
    float boundingBoxSize = 0.2f;
    math::Vec3 downRight(topLeft.x + boundingBoxSize, topLeft.y + boundingBoxSize, 0.0f);

    for (auto obj : world->GameObjects) {
        auto objPos = obj->transform->position;

        if (objPos.x >= topLeft.x && objPos.x <= downRight.x) {
            fmt::println("Inside");
        }
    }
}
