#pragma once
#include "ecs/component.hpp"

class FoodComponent : public Component {
  public:
    FoodComponent();

    void Init() override;
    void Update() override;
};
