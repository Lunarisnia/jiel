#pragma once

namespace math {

constexpr float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

} // namespace math
