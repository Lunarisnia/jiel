#pragma once

#include "ecs/component.hpp"
#include "math/vec3.hpp"

class Transform : public Component {
  public:
    Transform() : Component("Transform") {}
    explicit Transform(const math::Vec3& position) : Component("Transform"), position(position) {}

    math::Vec3 position{};
};
