#pragma once

#include "ecs/component.hpp"
#include "math/mat4.hpp"

#include <optional>

class CameraComponent : public Component {
  public:
    CameraComponent() : Component("CameraComponent") {}

    float fieldOfView = 60.0F;
    float aspectRatio = 16.0F / 9.0F;
    float nearClip = 0.1F;
    float farClip = 1000.0F;

  public:
    [[nodiscard]] std::optional<math::Mat4> View() const;
    [[nodiscard]] std::optional<math::Mat4> Projection() const;
};
