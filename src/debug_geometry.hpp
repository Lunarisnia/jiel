#pragma once

#include "graphics/mesh.hpp"
#include "debug_renderer.hpp"
#include "math/mat4.hpp"
#include "math/vec3.hpp"

#include <vector>
#include <cstddef>

namespace debug_geometry {

std::size_t BatchIndex(DebugDepth depth);

void AppendLine(std::vector<MeshVertex>& vertices, const math::Vec3& start,
                const math::Vec3& end, const math::Vec3& color);
void AppendBox(std::vector<MeshVertex>& vertices, const Bounds& bounds,
               const math::Mat4& transform, const math::Vec3& color);

} // namespace debug_geometry
