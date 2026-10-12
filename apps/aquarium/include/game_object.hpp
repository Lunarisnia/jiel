#pragma once

#include "ecs/component.hpp"
#include <memory>
#include <vector>
class GameObject {
  private:
    std::vector<std::shared_ptr<Component>> components;

  public:
    void Init();
    void Update();

    void AddComponent(std::shared_ptr<Component>);
};
