#pragma once

#include "ecs/component.hpp"
#include "time.hpp"

class FishComponent : public Component {
  private:
    Time time;

  public:
    FishComponent();

    void Init() override;
    void Update() override;
};
