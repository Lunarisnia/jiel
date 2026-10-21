#pragma once

#include "debug_renderer.hpp"
#include "graphics/mesh.hpp"
#include "math/mat4.hpp"
#include "math/vec3.hpp"

#include <cstddef>
#include <vector>

namespace debug_geometry {

std::size_t BatchIndex(DebugDepth depth);

void AppendLine(std::vector<MeshVertex>& vertices, const math::Vec3& start,
                const math::Vec3& end, const math::Vec3& color);
void AppendBox(std::vector<MeshVertex>& vertices, const Bounds& bounds,
               const math::Mat4& transform, const math::Vec3& color);
void AppendCircle(std::vector<MeshVertex>& vertices, const math::Vec3& center, float radius,
                  const math::Mat4& transform, const math::Vec3& color);

} // namespace debug_geometry
