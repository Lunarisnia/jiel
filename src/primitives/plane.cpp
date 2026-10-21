#include "primitives/plane.hpp"
#include "graphics/mesh.hpp"
#include <array>
#include <cstdint>

namespace primitive {
Mesh CreatePlane() {
    // clang-format off
    std::array<MeshVertex, 4> points = {
        MeshVertex{{-0.5f, 0.5f, 0.0f}},
        MeshVertex{{-0.5f, -0.5f, 0.0f}},
        MeshVertex{{0.5f, -0.5f, 0.0f}},
        MeshVertex{{0.5f, 0.5f, 0.0f}},
    };
    std::array<std::uint32_t, 6> indices = {
        0, 1, 2,
        2, 3, 0,
    };
    // clang-format on

    MeshData meshData{};
    for (const std::uint32_t index : indices) {
        meshData.indices.emplace_back(index);
    }
    for (const MeshVertex& vertex : points) {
        meshData.vertices.emplace_back(vertex);
    }
    Mesh mesh{meshData};

    return mesh;
};
} // namespace primitive
