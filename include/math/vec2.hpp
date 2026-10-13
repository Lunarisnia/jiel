#pragma once

#include <cassert>
#include <cmath>

namespace math {

class Vec2 {
public:
    float x{};
    float y{};

    constexpr Vec2() = default;
    constexpr Vec2(float x, float y) : x(x), y(y) {}

    constexpr Vec2 operator+(const Vec2& other) const
    {
        return Vec2{x + other.x, y + other.y};
    }

    constexpr Vec2 operator+(float scalar) const
    {
        return Vec2{x + scalar, y + scalar};
    }

    constexpr Vec2 operator-(const Vec2& other) const
    {
        return Vec2{x - other.x, y - other.y};
    }

    constexpr Vec2 operator-() const { return Vec2{-x, -y}; }

    constexpr Vec2 operator/(float scalar) const
    {
        assert(scalar != 0.0F);
        return Vec2{x / scalar, y / scalar};
    }

    constexpr float dot(const Vec2& other) const { return x * other.x + y * other.y; }
    constexpr float lengthSquared() const { return dot(*this); }
    float length() const { return std::sqrt(lengthSquared()); }

    Vec2 normalized() const
    {
        const float magnitude = length();
        if (magnitude == 0.0F) {
            return *this;
        }
        return *this / magnitude;
    }
};

} // namespace math
