#pragma once

#include <cassert>
#include <cmath>

namespace math {

class Vec4 {
public:
    float x{};
    float y{};
    float z{};
    float w{};

    constexpr Vec4() = default;
    constexpr Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    constexpr Vec4 operator+(const Vec4& other) const
    {
        return Vec4{x + other.x, y + other.y, z + other.z, w + other.w};
    }

    constexpr Vec4 operator+(float scalar) const
    {
        return Vec4{x + scalar, y + scalar, z + scalar, w + scalar};
    }

    constexpr Vec4 operator-(const Vec4& other) const
    {
        return Vec4{x - other.x, y - other.y, z - other.z, w - other.w};
    }

    constexpr Vec4 operator-() const { return Vec4{-x, -y, -z, -w}; }

    constexpr Vec4 operator/(float scalar) const
    {
        assert(scalar != 0.0F);
        return Vec4{x / scalar, y / scalar, z / scalar, w / scalar};
    }

    constexpr float dot(const Vec4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    constexpr float lengthSquared() const { return dot(*this); }
    float length() const { return std::sqrt(lengthSquared()); }

    Vec4 normalized() const
    {
        const float magnitude = length();
        if (magnitude == 0.0F) {
            return *this;
        }
        return *this / magnitude;
    }
};

} // namespace math
