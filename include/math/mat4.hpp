#pragma once

#include "math/vec4.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <optional>

namespace math {

class Mat4 {
public:
    static constexpr Mat4 Zero()
    {
        return Mat4{{
            0.0F, 0.0F, 0.0F, 0.0F,
            0.0F, 0.0F, 0.0F, 0.0F,
            0.0F, 0.0F, 0.0F, 0.0F,
            0.0F, 0.0F, 0.0F, 0.0F,
        }};
    }

    static constexpr Mat4 Identity()
    {
        return Mat4{{
            1.0F, 0.0F, 0.0F, 0.0F,
            0.0F, 1.0F, 0.0F, 0.0F,
            0.0F, 0.0F, 1.0F, 0.0F,
            0.0F, 0.0F, 0.0F, 1.0F,
        }};
    }

    constexpr explicit Mat4(std::array<float, 16> values) : m_(values) {}

    constexpr float& operator()(std::size_t row, std::size_t column)
    {
        assert(row < 4 && column < 4);
        return m_[row * 4 + column];
    }

    constexpr float operator()(std::size_t row, std::size_t column) const
    {
        assert(row < 4 && column < 4);
        return m_[row * 4 + column];
    }

    constexpr Mat4 operator+(const Mat4& other) const
    {
        Mat4 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] + other.m_[index];
        }
        return result;
    }

    constexpr Mat4 operator-(const Mat4& other) const
    {
        Mat4 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] - other.m_[index];
        }
        return result;
    }

    constexpr Mat4 operator*(float scalar) const
    {
        Mat4 result = Zero();
        for (std::size_t index = 0; index < m_.size(); ++index) {
            result.m_[index] = m_[index] * scalar;
        }
        return result;
    }

    constexpr Mat4 operator*(const Mat4& other) const
    {
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

    constexpr Vec4 operator*(const Vec4& vector) const
    {
        return Vec4{
            (*this)(0, 0) * vector.x() + (*this)(0, 1) * vector.y() +
                (*this)(0, 2) * vector.z() + (*this)(0, 3) * vector.w(),
            (*this)(1, 0) * vector.x() + (*this)(1, 1) * vector.y() +
                (*this)(1, 2) * vector.z() + (*this)(1, 3) * vector.w(),
            (*this)(2, 0) * vector.x() + (*this)(2, 1) * vector.y() +
                (*this)(2, 2) * vector.z() + (*this)(2, 3) * vector.w(),
            (*this)(3, 0) * vector.x() + (*this)(3, 1) * vector.y() +
                (*this)(3, 2) * vector.z() + (*this)(3, 3) * vector.w(),
        };
    }

    constexpr void T()
    {
        Mat4 result = Zero();
        for (std::size_t row = 0; row < 4; ++row) {
            for (std::size_t column = 0; column < 4; ++column) {
                result(column, row) = (*this)(row, column);
            }
        }
        m_ = result.m_;
    }

    constexpr float determinant() const
    {
        float result = 0.0F;
        for (std::size_t column = 0; column < 4; ++column) {
            const float sign = column % 2 == 0 ? 1.0F : -1.0F;
            result += sign * (*this)(0, column) * minorDeterminant(0, column);
        }
        return result;
    }

    constexpr std::optional<Mat4> inverse() const
    {
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
    constexpr float minorDeterminant(std::size_t excluded_row,
                                     std::size_t excluded_column) const
    {
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
