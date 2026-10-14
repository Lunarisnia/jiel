#pragma once

#include "ecs/component.hpp"

class TriggerBoxComponent : public Component {
  public:
    TriggerBoxComponent();

    void Init() override;
    void Update() override;
};
