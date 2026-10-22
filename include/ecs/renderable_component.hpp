#pragma once

#include "ecs/component.hpp"

#include <string>
#include <utility>

class RenderableComponent : public Component {
  public:
    explicit RenderableComponent(std::string id) : Component(std::move(id)) {}

    virtual void Render() = 0;
};
