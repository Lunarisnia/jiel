#include "debug_geometry.hpp"

#include "math/vec4.hpp"

#include <array>
#include <cstddef>

namespace {
math::Vec3 TransformPoint(const math::Mat4& transform, const math::Vec3& point) {
    const math::Vec4 transformed = transform * math::Vec4{point.x, point.y, point.z, 1.0F};
    return {transformed.x, transformed.y, transformed.z};
}
} // namespace

namespace debug_geometry {

std::size_t BatchIndex(DebugDepth depth) {
    return depth == DebugDepth::Tested ? 0U : 1U;
}

void AppendLine(std::vector<MeshVertex>& vertices, const math::Vec3& start,
                const math::Vec3& end, const math::Vec3& color) {
    vertices.push_back({start, color});
    vertices.push_back({end, color});
}

void AppendBox(std::vector<MeshVertex>& vertices, const Bounds& bounds,
               const math::Mat4& transform, const math::Vec3& color) {
    const std::array corners = {
        math::Vec3{bounds.minimum.x, bounds.minimum.y, bounds.minimum.z},
        math::Vec3{bounds.maximum.x, bounds.minimum.y, bounds.minimum.z},
        math::Vec3{bounds.maximum.x, bounds.maximum.y, bounds.minimum.z},
        math::Vec3{bounds.minimum.x, bounds.maximum.y, bounds.minimum.z},
        math::Vec3{bounds.minimum.x, bounds.minimum.y, bounds.maximum.z},
        math::Vec3{bounds.maximum.x, bounds.minimum.y, bounds.maximum.z},
        math::Vec3{bounds.maximum.x, bounds.maximum.y, bounds.maximum.z},
        math::Vec3{bounds.minimum.x, bounds.maximum.y, bounds.maximum.z},
    };
    constexpr std::array<std::array<std::size_t, 2>, 12> edges = {{
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6},
        {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7},
    }};

    for (const auto& edge : edges) {
        AppendLine(vertices, TransformPoint(transform, corners[edge[0]]),
                   TransformPoint(transform, corners[edge[1]]), color);
    }
}

} // namespace debug_geometry
