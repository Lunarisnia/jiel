#include "ecs/camera_component.hpp"

#include "game_object.hpp"

#include <cmath>
#include <numbers>

std::optional<math::Mat4> CameraComponent::View() const {
    if (!gameObject || !gameObject->transform) {
        return std::nullopt;
    }

    return gameObject->transform->Model().inverse();
}

std::optional<math::Mat4> CameraComponent::Projection() const {
    if (!(fieldOfView > 0.0F && fieldOfView < 180.0F) || !(aspectRatio > 0.0F) ||
        !(nearClip > 0.0F && nearClip < farClip) || !std::isfinite(fieldOfView) ||
        !std::isfinite(aspectRatio) || !std::isfinite(nearClip) || !std::isfinite(farClip)) {
        return std::nullopt;
    }

    const float radians = fieldOfView * std::numbers::pi_v<float> / 180.0F;
    const float tangent = std::tan(radians / 2.0F);
    if (!(tangent > 0.0F) || !std::isfinite(tangent)) {
        return std::nullopt;
    }

    math::Mat4 projection = math::Mat4::Zero();
    projection(0, 0) = 1.0F / (aspectRatio * tangent);
    projection(1, 1) = 1.0F / tangent;
    projection(2, 2) = -(farClip + nearClip) / (farClip - nearClip);
    projection(2, 3) = -(2.0F * farClip * nearClip) / (farClip - nearClip);
    projection(3, 2) = -1.0F;
    return projection;
}
