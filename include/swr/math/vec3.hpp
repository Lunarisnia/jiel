#pragma once

#include <cassert>
#include <cmath>

namespace swr::math {

class Vec3 {
public:
    constexpr Vec3() = default;
    constexpr Vec3(float x, float y, float z) : x_(x), y_(y), z_(z) {}

    constexpr float x() const { return x_; }
    constexpr float y() const { return y_; }
    constexpr float z() const { return z_; }

    constexpr Vec3 operator+(const Vec3& other) const
    {
        return Vec3{x_ + other.x_, y_ + other.y_, z_ + other.z_};
    }

    constexpr Vec3 operator+(float scalar) const
    {
        return Vec3{x_ + scalar, y_ + scalar, z_ + scalar};
    }

    constexpr Vec3 operator-(const Vec3& other) const
    {
        return Vec3{x_ - other.x_, y_ - other.y_, z_ - other.z_};
    }

    constexpr Vec3 operator-() const { return Vec3{-x_, -y_, -z_}; }

    constexpr Vec3 operator/(float scalar) const
    {
        assert(scalar != 0.0F);
        return Vec3{x_ / scalar, y_ / scalar, z_ / scalar};
    }

    constexpr float dot(const Vec3& other) const
    {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    constexpr Vec3 cross(const Vec3& other) const
    {
        return Vec3{
            y_ * other.z_ - z_ * other.y_,
            z_ * other.x_ - x_ * other.z_,
            x_ * other.y_ - y_ * other.x_,
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

private:
    float x_{};
    float y_{};
    float z_{};
};

} // namespace swr::math
