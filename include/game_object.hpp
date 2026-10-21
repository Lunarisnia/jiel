#pragma once

#include "ecs/component.hpp"
#include "ecs/transform_component.hpp"
#include <memory>
#include <vector>

class GameObject {
  private:
    std::vector<std::shared_ptr<Component>> components;

  public:
    unsigned int ID;

  public:
    GameObject();

    void Init();
    void Update();

    template <typename T> [[nodiscard]] std::shared_ptr<T> GetComponent() const {
        for (const auto& component : components) {
            if (auto result = std::dynamic_pointer_cast<T>(component)) {
                return result;
            }
        }
        return nullptr;
    }

    void AddComponent(std::shared_ptr<Component>);

    std::shared_ptr<TransformComponent> transform;
};
