#pragma once

#include "ecs/renderable_component.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"

#include <memory>
#include <utility>

class MeshRendererComponent : public RenderableComponent {
  public:
    MeshRendererComponent() : RenderableComponent("MeshRendererComponent") {}
    MeshRendererComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
        : RenderableComponent("MeshRendererComponent"), mesh(std::move(mesh)),
          material(std::move(material)) {}

    std::shared_ptr<Mesh> mesh{};
    std::shared_ptr<Material> material{};

  public:
    void Render() override;
};
