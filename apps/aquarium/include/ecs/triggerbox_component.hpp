#pragma once

#include "debug_renderer.hpp"
#include "ecs/component.hpp"
#include "world.hpp"
#include <memory>

class TriggerBoxComponent : public Component {
  private:
    std::shared_ptr<World> world;
    DebugRenderer& debugRenderer;

    bool inside;

  public:
    TriggerBoxComponent(std::shared_ptr<World> world, DebugRenderer& debugRenderer);

    void Init() override;
    void Update() override;
};
