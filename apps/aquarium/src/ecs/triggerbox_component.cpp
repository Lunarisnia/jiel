#include "ecs/triggerbox_component.hpp"
#include "debug_renderer.hpp"
#include "fmt/base.h"
#include "math/vec3.hpp"
#include "world.hpp"
#include <memory>

TriggerBoxComponent::TriggerBoxComponent(std::shared_ptr<World> world, DebugRenderer& dbgRend)
    : Component("TriggerBoxComponent"), world(std::move(world)), debugRenderer(dbgRend) {}

void TriggerBoxComponent::Init() {}

void TriggerBoxComponent::Update() {
    float boundingBoxSize = 1.0f;
    math::Vec3 topLeft(gameObject->transform->position.x - boundingBoxSize / 2,
                       gameObject->transform->position.y - boundingBoxSize, -0.5f);
    math::Vec3 downRight(topLeft.x + boundingBoxSize, topLeft.y + boundingBoxSize, 0.5f);

    math::Vec3 color = inside ? math::Vec3(0.0f, 1.0f, 0.0f) : math::Vec3(1.0f, 0.0f, 0.0f);
    debugRenderer.DrawBox({{topLeft.x, topLeft.y, -0.5f}, {downRight.x, downRight.y, 0.5f}},
                          gameObject->transform->Model(), color);

    for (auto obj : world->GameObjects) {
        if (obj->ID == gameObject->ID) {
            continue;
        }
        auto objPos = obj->transform->position;

        inside = (objPos.x >= topLeft.x) && (objPos.x <= downRight.x);

        debugRenderer.DrawCircle(obj->transform->position, 0.5f, obj->transform->Model(), color);
    }
}
