#include "primitives/plane.hpp"
#include "glad/gl.h"
#include "graphics/mesh.hpp"
#include "math/vec3.hpp"
#include <array>

namespace primitive {
Mesh CreatePlane() {
    // clang-format off
    std::array<math::Vec3, 6> points = {
        math::Vec3(-0.5f, 0.5f, 0.0f),
        math::Vec3(-0.5f, -0.5f, 0.0f),
        math::Vec3(0.5f, -0.5f, 0.0f),
        math::Vec3(0.5f, 0.5f, 0.0f),
    };
    std::array<GLuint, 6> indice = {
        0, 1, 2,
        2, 3, 0,
    };
    // clang-format on

    MeshData meshData{};
    for (const GLuint& i : indice) {
        meshData.indice.emplace_back(i);
    }
    for (const math::Vec3& vertex : points) {
        meshData.vertice.emplace_back(vertex);
    }
    Mesh mesh{meshData};

    return mesh;
};
} // namespace primitive
