#include "primitives/triangle.hpp"
#include "glad/gl.h"
#include "graphics/mesh.hpp"
#include "math/vec3.hpp"
#include <array>
namespace primitive {
Mesh CreateTriangle() {
    MeshData meshData{};
    std::array<math::Vec3, 3> vertice = {
        math::Vec3(-0.5, -0.5, -0.5),
        math::Vec3(0.0, 0.5, 0.0),
        math::Vec3(0.5, -0.5, -0.5),
    };
    std::array<GLuint, 3> indice = {0, 1, 2};
    for (const auto v : vertice) {
        meshData.vertice.emplace_back(v);
    }
    for (const auto i : indice) {
        meshData.indice.emplace_back(i);
    }

    return Mesh{meshData};
};
}; // namespace primitive
