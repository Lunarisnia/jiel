#pragma once

#include "ecs/component.hpp"
#include "ecs/mesh_renderer_component.hpp"
#include "math/mat4.hpp"
#include "math/vec3.hpp"

#include <cmath>
#include <memory>
#include <numbers>

class TransformComponent : public Component {
  private:
    std::shared_ptr<MeshRendererComponent> meshRenderer;

  public:
    math::Vec3 position{};
    math::Vec3 rotation{};
    math::Vec3 scale{1.0F, 1.0F, 1.0F};

  public:
    TransformComponent() : Component("TransformComponent") {}
    explicit TransformComponent(const math::Vec3& position)
        : Component("TransformComponent"), position(position) {}

    [[nodiscard]] math::Mat4 Model() const {
        math::Mat4 translationMatrix = math::Mat4::Identity();
        translationMatrix(0, 3) = position.x;
        translationMatrix(1, 3) = position.y;
        translationMatrix(2, 3) = position.z;

        math::Mat4 scaleMatrix = math::Mat4::Identity();
        scaleMatrix(0, 0) = scale.x;
        scaleMatrix(1, 1) = scale.y;
        scaleMatrix(2, 2) = scale.z;

        constexpr float degreesToRadians = std::numbers::pi_v<float> / 180.0F;
        const float x = rotation.x * degreesToRadians;
        const float y = rotation.y * degreesToRadians;
        const float z = rotation.z * degreesToRadians;

        math::Mat4 rotationX = math::Mat4::Identity();
        rotationX(1, 1) = std::cos(x);
        rotationX(1, 2) = -std::sin(x);
        rotationX(2, 1) = std::sin(x);
        rotationX(2, 2) = std::cos(x);

        math::Mat4 rotationY = math::Mat4::Identity();
        rotationY(0, 0) = std::cos(y);
        rotationY(0, 2) = std::sin(y);
        rotationY(2, 0) = -std::sin(y);
        rotationY(2, 2) = std::cos(y);

        math::Mat4 rotationZ = math::Mat4::Identity();
        rotationZ(0, 0) = std::cos(z);
        rotationZ(0, 1) = -std::sin(z);
        rotationZ(1, 0) = std::sin(z);
        rotationZ(1, 1) = std::cos(z);

        return translationMatrix * rotationZ * rotationY * rotationX * scaleMatrix;
    }

    void Init() override;
    void Update() override;
};
