#include "debug_geometry.hpp"

#include <vector>

namespace {
bool Equal(const math::Vec3& left, const math::Vec3& right) {
    return left.x == right.x && left.y == right.y && left.z == right.z;
}
} // namespace

int main() {
    if (debug_geometry::BatchIndex(DebugDepth::Tested) != 0 ||
        debug_geometry::BatchIndex(DebugDepth::AlwaysVisible) != 1) {
        return 1;
    }

    math::Mat4 transform = math::Mat4::Identity();
    transform(0, 3) = 3.0F;
    transform(1, 3) = 4.0F;
    transform(2, 3) = 5.0F;

    const Bounds bounds{{-1.0F, -2.0F, -3.0F}, {1.0F, 2.0F, 3.0F}};
    const math::Vec3 color{0.25F, 0.5F, 0.75F};
    std::vector<MeshVertex> vertices{};
    debug_geometry::AppendBox(vertices, bounds, transform, color);

    if (vertices.size() != 24 || !Equal(vertices[0].position, {2.0F, 2.0F, 2.0F}) ||
        !Equal(vertices[1].position, {4.0F, 2.0F, 2.0F})) {
        return 1;
    }
    for (const MeshVertex& vertex : vertices) {
        if (!Equal(vertex.color, color)) {
            return 1;
        }
    }

    return 0;
}
