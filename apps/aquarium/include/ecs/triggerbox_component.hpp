#pragma once

#include "ecs/component.hpp"
#include "world.hpp"
#include <memory>

class TriggerBoxComponent : public Component {
  private:
    std::shared_ptr<World> world;

  public:
    TriggerBoxComponent(std::shared_ptr<World> world);

    void Init() override;
    void Update() override;
};
