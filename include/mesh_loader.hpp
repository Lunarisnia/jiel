#pragma once

#include "graphics/mesh.hpp"
#include <expected>
#include <string>

class MeshLoader {
  public:
    [[nodiscard]] static std::expected<Mesh, std::string> LoadOBJ(const std::string& path);
};
