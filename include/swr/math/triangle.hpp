#pragma once

namespace swr::math {

constexpr double SignedTriangleArea(int ax, int ay, int bx, int by, int cx, int cy)
{
    return 0.5 * ((by - ay) * (bx + ax) + (cy - by) * (cx + bx) +
                  (ay - cy) * (ax + cx));
}

} // namespace swr::math
