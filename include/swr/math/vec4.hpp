#pragma once

#include <cassert>
#include <cmath>

namespace swr::math {

class Vec4 {
public:
    constexpr Vec4() = default;
    constexpr Vec4(float x, float y, float z, float w) : x_(x), y_(y), z_(z), w_(w) {}

    constexpr float x() const { return x_; }
    constexpr float y() const { return y_; }
    constexpr float z() const { return z_; }
    constexpr float w() const { return w_; }

    constexpr Vec4 operator+(const Vec4& other) const
    {
        return Vec4{x_ + other.x_, y_ + other.y_, z_ + other.z_, w_ + other.w_};
    }

    constexpr Vec4 operator+(float scalar) const
    {
        return Vec4{x_ + scalar, y_ + scalar, z_ + scalar, w_ + scalar};
    }

    constexpr Vec4 operator-(const Vec4& other) const
    {
        return Vec4{x_ - other.x_, y_ - other.y_, z_ - other.z_, w_ - other.w_};
    }

    constexpr Vec4 operator-() const { return Vec4{-x_, -y_, -z_, -w_}; }

    constexpr Vec4 operator/(float scalar) const
    {
        assert(scalar != 0.0F);
        return Vec4{x_ / scalar, y_ / scalar, z_ / scalar, w_ / scalar};
    }

    constexpr float dot(const Vec4& other) const
    {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_ + w_ * other.w_;
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

private:
    float x_{};
    float y_{};
    float z_{};
    float w_{};
};

} // namespace swr::math
