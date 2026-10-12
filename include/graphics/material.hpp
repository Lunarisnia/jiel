#pragma once

#include "graphics/shader.hpp"

#include <memory>
#include <utility>

class Material {
  public:
    explicit Material(std::shared_ptr<Shader> shader) : shader(std::move(shader)) {}

    void Bind() const;

    std::shared_ptr<Shader> shader;
};
