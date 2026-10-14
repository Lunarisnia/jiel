#pragma once

#include "ecs/component.hpp"

#include <memory>

class MeshRendererComponent;

class FishComponent : public Component {
  private:
    std::shared_ptr<MeshRendererComponent> meshRenderer;

  public:
    FishComponent();

    void Init() override;
    void Update() override;
};
