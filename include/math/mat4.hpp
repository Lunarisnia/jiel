#pragma once

#include "math/vec3.hpp"
#include "math/vec4.hpp"

#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <limits>
#include <optional>

namespace math {

class Mat4 {
  public:
    static constexpr Mat4 Zero() {
        return Mat4{{
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
        }};
    }

    static constexpr Mat4 Identity() {
        return Mat4{{
            1.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            1.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            1.0F,
            0.0F,
            0.0F,
            0.0F,
            0.0F,
            1.0F,
        }};
    }

    static std::optional<Mat4> LookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
        const Vec3 backward = eye - center;
        const float backwardLength = backward.length();
        if (!(backwardLength > 0.0F) || !std::isfinite(backwardLength)) {
            return std::nullopt;
        }

        const Vec3 n = backward / backwardLength;
        const Vec3 right = up.cross(n);
        const float rightLength = right.length();
        if (!(rightLength > 0.0F) || !std::isfinite(rightLength)) {
            return std::nullopt;
        }

        const Vec3 l = right / rightLength;
        const Vec3 m = n.cross(l);
        Mat4 view = Identity();
        view(0, 0) = l.x;
        view(0, 1) = l.y;
        view(0, 2) = l.z;
        view(1, 0) = m.x;
        view(1, 1) = m.y;
        view(1, 2) = m.z;
        view(2, 0) = n.x;
        view(2, 1) = n.y;
        view(2, 2) = n.z;
        view(0, 3) = -l.dot(eye);
        view(1, 3) = -m.dot(eye);
        view(2, 3) = -n.dot(eye);
        return view;
    }

    static std::optional<Mat4> Orthographic(float left, float right, float bottom, float top,
                                            float near, float far) {
        if (!std::isfinite(left) || !std::isfinite(right) || !std::isfinite(bottom) ||
            !std::isfinite(top) || !std::isfinite(near) || !std::isfinite(far) || !(left < right) ||
            !(bottom < top) || !(near > 0.0F) || !(near < far)) {
            return std::nullopt;
        }

        const float width = right - left;
        const float height = top - bottom;
        const float depth = far - near;
        if (!std::isfinite(width) || !std::isfinite(height) || !std::isfinite(depth)) {
            return std::nullopt;
        }

        Mat4 projection = Identity();
        projection(0, 0) = 2.0F / width;
        projection(1, 1) = 2.0F / height;
        projection(2, 2) = -2.0F / depth;
        projection(0, 3) = -(right + left) / width;
        projection(1, 3) = -(top + bottom) / height;
        projection(2, 3) = -(far + near) / depth;
        return projection;
    }

    constexpr explicit Mat4(std::array<float, 16> values) : m_(values) {}

    constexpr const float* Data() const {
        return m_.data();
    }
    constexpr float* Data() {
        return m_.data();
    }

    constexpr float& operator()(std::size_t row, std::size_t column) {
        assert(row < 4 && column < 4);
        return m_[row * 4 + column];
    }

    constexpr float operator()(std::size_t row, std::size_t column) const {
        assert(row < 4 && column < 4);
        return m_[row * 4 + column];
    }

    constexpr Mat4 operator+(const Mat4& other) const {
        Mat4 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] + other.m_[index];
        }
        return result;
    }

    constexpr Mat4 operator-(const Mat4& other) const {
        Mat4 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] - other.m_[index];
        }
        return result;
    }

    constexpr Mat4 operator*(float scalar) const {
        Mat4 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] * scalar;
        }
        return result;
    }

    constexpr Mat4 operator*(const Mat4& other) const {
        Mat4 result = Zero();
        for (std::size_t row = 0; row < 4; ++row) {
            for (std::size_t column = 0; column < 4; ++column) {
                for (std::size_t index = 0; index < 4; ++index) {
                    result(row, column) += (*this)(row, index) * other(index, column);
                }
            }
        }
        return result;
    }

    constexpr Vec4 operator*(const Vec4& vector) const {
        return Vec4{
            (*this)(0, 0) * vector.x + (*this)(0, 1) * vector.y + (*this)(0, 2) * vector.z +
                (*this)(0, 3) * vector.w,
            (*this)(1, 0) * vector.x + (*this)(1, 1) * vector.y + (*this)(1, 2) * vector.z +
                (*this)(1, 3) * vector.w,
            (*this)(2, 0) * vector.x + (*this)(2, 1) * vector.y + (*this)(2, 2) * vector.z +
                (*this)(2, 3) * vector.w,
            (*this)(3, 0) * vector.x + (*this)(3, 1) * vector.y + (*this)(3, 2) * vector.z +
                (*this)(3, 3) * vector.w,
        };
    }

    constexpr void T() {
        Mat4 result = Zero();
        for (std::size_t row = 0; row < 4; ++row) {
            for (std::size_t column = 0; column < 4; ++column) {
                result(column, row) = (*this)(row, column);
            }
        }
        m_ = result.m_;
    }

    constexpr float determinant() const {
        float result = 0.0F;
        for (std::size_t column = 0; column < 4; ++column) {
            const float sign = column % 2 == 0 ? 1.0F : -1.0F;
            result += sign * (*this)(0, column) * minorDeterminant(0, column);
        }
        return result;
    }

    constexpr std::optional<Mat4> inverse() const {
        const float determinant_value = determinant();
        if (determinant_value >= -std::numeric_limits<float>::epsilon() &&
            determinant_value <= std::numeric_limits<float>::epsilon()) {
            return std::nullopt;
        }

        Mat4 result = Zero();
        const float inverse_determinant = 1.0F / determinant_value;
        for (std::size_t row = 0; row < 4; ++row) {
            for (std::size_t column = 0; column < 4; ++column) {
                const float sign = (row + column) % 2 == 0 ? 1.0F : -1.0F;
                result(column, row) = sign * minorDeterminant(row, column) * inverse_determinant;
            }
        }
        return result;
    }

  private:
    constexpr float minorDeterminant(std::size_t excluded_row, std::size_t excluded_column) const {
        std::array<float, 9> values{};
        std::size_t index = 0;
        for (std::size_t row = 0; row < 4; ++row) {
            if (row == excluded_row) {
                continue;
            }
            for (std::size_t column = 0; column < 4; ++column) {
                if (column != excluded_column) {
                    values[index++] = (*this)(row, column);
                }
            }
        }

        return values[0] * (values[4] * values[8] - values[5] * values[7]) -
               values[1] * (values[3] * values[8] - values[5] * values[6]) +
               values[2] * (values[3] * values[7] - values[4] * values[6]);
    }

    std::array<float, 16> m_{};
};

} // namespace math
