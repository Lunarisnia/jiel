#pragma once

namespace swr::math {

constexpr float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

} // namespace swr::math
