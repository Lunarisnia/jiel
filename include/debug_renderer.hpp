#pragma once

#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "math/mat4.hpp"
#include "math/vec3.hpp"

#include <expected>
#include <array>
#include <string>
#include <vector>

enum class DebugDepth {
    Tested,
    AlwaysVisible,
};

struct Bounds {
    math::Vec3 minimum{};
    math::Vec3 maximum{};
};

class DebugRenderer {
  public:
    static std::expected<DebugRenderer, std::string> Create();

    DebugRenderer(const DebugRenderer&) = delete;
    DebugRenderer& operator=(const DebugRenderer&) = delete;
    DebugRenderer(DebugRenderer&&) noexcept = default;
    DebugRenderer& operator=(DebugRenderer&&) noexcept = default;

    void DrawLine(const math::Vec3& start, const math::Vec3& end,
                  const math::Vec3& color = {1.0F, 1.0F, 1.0F},
                  DebugDepth depth = DebugDepth::Tested);
    void DrawBox(const Bounds& localBounds, const math::Mat4& transform,
                 const math::Vec3& color = {1.0F, 1.0F, 1.0F},
                 DebugDepth depth = DebugDepth::Tested);
    void DrawCircle(const math::Vec3& localCenter, float radius, const math::Mat4& transform,
                    const math::Vec3& color = {1.0F, 1.0F, 1.0F},
                    DebugDepth depth = DebugDepth::Tested);

    void Render();

  private:
    DebugRenderer(Shader shader, Mesh depthTestedMesh, Mesh alwaysVisibleMesh);
    std::vector<MeshVertex>& batch(DebugDepth depth);
    void drawBatch(Mesh& mesh, std::vector<MeshVertex>& vertices, bool depthTested);

    Shader shader;
    Mesh depthTestedMesh;
    Mesh alwaysVisibleMesh;
    std::array<std::vector<MeshVertex>, 2> batches{};
};
