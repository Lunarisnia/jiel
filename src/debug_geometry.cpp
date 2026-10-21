#include "debug_geometry.hpp"

#include "math/vec4.hpp"

#include <array>
#include <cmath>
#include <cstddef>
#include <numbers>

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

void AppendCircle(std::vector<MeshVertex>& vertices, const math::Vec3& center, float radius,
                  const math::Mat4& transform, const math::Vec3& color) {
    if (!(radius > 0.0F) || !std::isfinite(radius)) {
        return;
    }

    constexpr int segments = 32;
    constexpr float fullTurn = 2.0F * std::numbers::pi_v<float>;
    for (int index = 0; index < segments; ++index) {
        const float angle = fullTurn * static_cast<float>(index) / static_cast<float>(segments);
        const float nextAngle =
            fullTurn * static_cast<float>(index + 1) / static_cast<float>(segments);
        const math::Vec3 start{center.x + radius * std::cos(angle),
                               center.y + radius * std::sin(angle), center.z};
        const math::Vec3 end = index + 1 == segments
                                   ? math::Vec3{center.x + radius, center.y, center.z}
                                   : math::Vec3{center.x + radius * std::cos(nextAngle),
                                                center.y + radius * std::sin(nextAngle), center.z};
        AppendLine(vertices, TransformPoint(transform, start), TransformPoint(transform, end),
                   color);
    }
}

} // namespace debug_geometry
