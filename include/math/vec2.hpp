#pragma once

#include <cassert>
#include <cmath>

namespace math {

class Vec2 {
public:
    constexpr Vec2() = default;
    constexpr Vec2(float x, float y) : x_(x), y_(y) {}

    constexpr float x() const { return x_; }
    constexpr float y() const { return y_; }

    constexpr Vec2 operator+(const Vec2& other) const
    {
        return Vec2{x_ + other.x_, y_ + other.y_};
    }

    constexpr Vec2 operator+(float scalar) const
    {
        return Vec2{x_ + scalar, y_ + scalar};
    }

    constexpr Vec2 operator-(const Vec2& other) const
    {
        return Vec2{x_ - other.x_, y_ - other.y_};
    }

    constexpr Vec2 operator-() const { return Vec2{-x_, -y_}; }

    constexpr Vec2 operator/(float scalar) const
    {
        assert(scalar != 0.0F);
        return Vec2{x_ / scalar, y_ / scalar};
    }

    constexpr float dot(const Vec2& other) const { return x_ * other.x_ + y_ * other.y_; }
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

private:
    float x_{};
    float y_{};
};

} // namespace math
