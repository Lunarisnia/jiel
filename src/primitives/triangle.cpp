#include "primitives/triangle.hpp"
#include "graphics/mesh.hpp"
#include <array>
#include <cstdint>
namespace primitive {
Mesh CreateTriangle() {
    MeshData meshData{};
    std::array<MeshVertex, 3> vertices = {
        MeshVertex{{-0.5F, -0.5F, -0.5F}},
        MeshVertex{{0.0F, 0.5F, 0.0F}},
        MeshVertex{{0.5F, -0.5F, -0.5F}},
    };
    std::array<std::uint32_t, 3> indices = {0, 1, 2};
    for (const auto& vertex : vertices) {
        meshData.vertices.emplace_back(vertex);
    }
    for (const auto index : indices) {
        meshData.indices.emplace_back(index);
    }

    return Mesh{meshData};
};
}; // namespace primitive
