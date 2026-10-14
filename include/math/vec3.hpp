#pragma once

#include <cassert>
#include <cmath>

namespace math {

class Vec3 {
public:
    float x{};
    float y{};
    float z{};

    constexpr Vec3() = default;
    constexpr Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    constexpr Vec3 operator+(const Vec3& other) const
    {
        return Vec3{x + other.x, y + other.y, z + other.z};
    }

    constexpr Vec3 operator+(float scalar) const
    {
        return Vec3{x + scalar, y + scalar, z + scalar};
    }

    constexpr Vec3 operator-(const Vec3& other) const
    {
        return Vec3{x - other.x, y - other.y, z - other.z};
    }

    constexpr Vec3 operator-() const { return Vec3{-x, -y, -z}; }

    constexpr Vec3& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    constexpr Vec3 operator/(float scalar) const
    {
        assert(scalar != 0.0F);
        return Vec3{x / scalar, y / scalar, z / scalar};
    }

    constexpr float dot(const Vec3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    constexpr Vec3 cross(const Vec3& other) const
    {
        return Vec3{
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
        };
    }

    constexpr float lengthSquared() const { return dot(*this); }
    float length() const { return std::sqrt(lengthSquared()); }

    Vec3 normalized() const
    {
        const float magnitude = length();
        if (magnitude == 0.0F) {
            return *this;
        }
        return *this / magnitude;
    }
};

} // namespace math
