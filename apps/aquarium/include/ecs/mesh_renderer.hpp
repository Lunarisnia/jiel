#pragma once

#include "ecs/component.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"

#include <memory>
#include <utility>

class MeshRenderer : public Component {
  public:
    MeshRenderer() : Component("MeshRenderer") {}
    MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
        : Component("MeshRenderer"), mesh(std::move(mesh)), material(std::move(material)) {}

    std::shared_ptr<Mesh> mesh{};
    std::shared_ptr<Material> material{};

  public:
    void Init() override;
    void Update() override;
};
