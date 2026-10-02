#pragma once

#include "math/vec3.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <optional>

namespace math {

class Mat3 {
public:
    static constexpr Mat3 Zero()
    {
        return Mat3{{0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F}};
    }

    static constexpr Mat3 Identity()
    {
        return Mat3{{
            1.0F, 0.0F, 0.0F,
            0.0F, 1.0F, 0.0F,
            0.0F, 0.0F, 1.0F,
        }};
    }

    constexpr explicit Mat3(std::array<float, 9> values) : m_(values) {}

    constexpr float& operator()(std::size_t row, std::size_t column)
    {
        assert(row < 3 && column < 3);
        return m_[row * 3 + column];
    }

    constexpr float operator()(std::size_t row, std::size_t column) const
    {
        assert(row < 3 && column < 3);
        return m_[row * 3 + column];
    }

    constexpr Mat3 operator+(const Mat3& other) const
    {
        Mat3 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] + other.m_[index];
        }
        return result;
    }

    constexpr Mat3 operator-(const Mat3& other) const
    {
        Mat3 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] - other.m_[index];
        }
        return result;
    }

    constexpr Mat3 operator*(float scalar) const
    {
        Mat3 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] * scalar;
        }
        return result;
    }

    constexpr Mat3 operator*(const Mat3& other) const
    {
        Mat3 result = Zero();
        for (std::size_t row = 0; row < 3; ++row) {
            for (std::size_t column = 0; column < 3; ++column) {
                for (std::size_t index = 0; index < 3; ++index) {
                    result(row, column) += (*this)(row, index) * other(index, column);
                }
            }
        }
        return result;
    }

    constexpr Vec3 operator*(const Vec3& vector) const
    {
        return Vec3{
            (*this)(0, 0) * vector.x() + (*this)(0, 1) * vector.y() +
                (*this)(0, 2) * vector.z(),
            (*this)(1, 0) * vector.x() + (*this)(1, 1) * vector.y() +
                (*this)(1, 2) * vector.z(),
            (*this)(2, 0) * vector.x() + (*this)(2, 1) * vector.y() +
                (*this)(2, 2) * vector.z(),
        };
    }

    constexpr void T()
    {
        Mat3 result = Zero();
        for (std::size_t row = 0; row < 3; ++row) {
            for (std::size_t column = 0; column < 3; ++column) {
                result(column, row) = (*this)(row, column);
            }
        }
        m_ = result.m_;
    }

    constexpr float determinant() const
    {
        const float m00 = (*this)(0, 0);
        const float m01 = (*this)(0, 1);
        const float m02 = (*this)(0, 2);
        const float m10 = (*this)(1, 0);
        const float m11 = (*this)(1, 1);
        const float m12 = (*this)(1, 2);
        const float m20 = (*this)(2, 0);
        const float m21 = (*this)(2, 1);
        const float m22 = (*this)(2, 2);

        return m00 * (m11 * m22 - m12 * m21) - m01 * (m10 * m22 - m12 * m20) +
               m02 * (m10 * m21 - m11 * m20);
    }

    constexpr std::optional<Mat3> inverse() const
    {
        const float m00 = (*this)(0, 0);
        const float m01 = (*this)(0, 1);
        const float m02 = (*this)(0, 2);
        const float m10 = (*this)(1, 0);
        const float m11 = (*this)(1, 1);
        const float m12 = (*this)(1, 2);
        const float m20 = (*this)(2, 0);
        const float m21 = (*this)(2, 1);
        const float m22 = (*this)(2, 2);

        const float determinant_value = determinant();
        if (determinant_value >= -std::numeric_limits<float>::epsilon() &&
            determinant_value <= std::numeric_limits<float>::epsilon()) {
            return std::nullopt;
        }
        const float inverse_determinant = 1.0F / determinant_value;

        return Mat3{{
            (m11 * m22 - m12 * m21) * inverse_determinant,
            (m02 * m21 - m01 * m22) * inverse_determinant,
            (m01 * m12 - m02 * m11) * inverse_determinant,
            (m12 * m20 - m10 * m22) * inverse_determinant,
            (m00 * m22 - m02 * m20) * inverse_determinant,
            (m02 * m10 - m00 * m12) * inverse_determinant,
            (m10 * m21 - m11 * m20) * inverse_determinant,
            (m01 * m20 - m00 * m21) * inverse_determinant,
            (m00 * m11 - m01 * m10) * inverse_determinant,
        }};
    }

private:
    std::array<float, 9> m_{};
};

} // namespace math
