#include "math/mat4.hpp"

#include <cmath>

namespace {
bool Near(float actual, float expected) {
    return std::abs(actual - expected) < 0.00001F;
}

bool NearPoint(const math::Vec4& actual, const math::Vec4& expected) {
    return Near(actual.x, expected.x) && Near(actual.y, expected.y) &&
           Near(actual.z, expected.z) && Near(actual.w, expected.w);
}
} // namespace

int main() {
    const auto view = math::Mat4::LookAt({2.0F, 3.0F, 5.0F}, {2.0F, 3.0F, 4.0F},
                                         {0.0F, 1.0F, 0.0F});
    if (!view || !NearPoint(*view * math::Vec4{2.0F, 3.0F, 5.0F, 1.0F},
                            {0.0F, 0.0F, 0.0F, 1.0F}) ||
        !NearPoint(*view * math::Vec4{2.0F, 3.0F, 4.0F, 1.0F},
                   {0.0F, 0.0F, -1.0F, 1.0F})) {
        return 1;
    }

    const auto turned = math::Mat4::LookAt({0.0F, 0.0F, 0.0F}, {1.0F, 0.0F, 0.0F},
                                           {0.0F, 1.0F, 0.0F});
    if (!turned || !NearPoint(*turned * math::Vec4{1.0F, 0.0F, 0.0F, 1.0F},
                              {0.0F, 0.0F, -1.0F, 1.0F}) ||
        math::Mat4::LookAt({}, {}, {0.0F, 1.0F, 0.0F}) ||
        math::Mat4::LookAt({}, {0.0F, 0.0F, -1.0F}, {0.0F, 0.0F, 1.0F})) {
        return 1;
    }

    const auto projection = math::Mat4::Orthographic(-2.0F, 6.0F, -3.0F, 1.0F,
                                                     1.0F, 9.0F);
    if (!projection ||
        !NearPoint(*projection * math::Vec4{-2.0F, -3.0F, -1.0F, 1.0F},
                   {-1.0F, -1.0F, -1.0F, 1.0F}) ||
        !NearPoint(*projection * math::Vec4{6.0F, 1.0F, -9.0F, 1.0F},
                   {1.0F, 1.0F, 1.0F, 1.0F}) ||
        !NearPoint(*projection * math::Vec4{2.0F, -1.0F, -5.0F, 1.0F},
                   {0.0F, 0.0F, 0.0F, 1.0F}) ||
        math::Mat4::Orthographic(1.0F, 1.0F, -1.0F, 1.0F, 1.0F, 9.0F) ||
        math::Mat4::Orthographic(-1.0F, 1.0F, -1.0F, 1.0F, 0.0F, 9.0F) ||
        math::Mat4::Orthographic(-1.0F, 1.0F, -1.0F, 1.0F, 9.0F, 1.0F)) {
        return 1;
    }
    return 0;
}
