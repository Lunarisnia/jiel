#include "debug_renderer.hpp"

#include "debug_geometry.hpp"
#include "file.hpp"

#include <glad/gl.h>

#include <exception>
#include <utility>

std::expected<DebugRenderer, std::string> DebugRenderer::Create() {
    try {
        Shader shader;
        if (auto result =
                shader.Add(File::LoadFile("assets/shaders/debug/debug.vert"), GL_VERTEX_SHADER);
            !result) {
            return std::unexpected(result.error());
        }
        if (auto result =
                shader.Add(File::LoadFile("assets/shaders/debug/debug.frag"), GL_FRAGMENT_SHADER);
            !result) {
            return std::unexpected(result.error());
        }
        if (auto result = shader.Compile(); !result) {
            return std::unexpected(result.error());
        }

        MeshData emptyMesh{};
        Mesh depthTestedMesh{emptyMesh, MeshTopology::Lines, MeshUsage::Dynamic};
        Mesh alwaysVisibleMesh{emptyMesh, MeshTopology::Lines, MeshUsage::Dynamic};
        return DebugRenderer{std::move(shader), std::move(depthTestedMesh),
                             std::move(alwaysVisibleMesh)};
    } catch (const std::exception& error) {
        return std::unexpected(error.what());
    }
}

DebugRenderer::DebugRenderer(Shader shader, Mesh depthTestedMesh, Mesh alwaysVisibleMesh)
    : shader(std::move(shader)), depthTestedMesh(std::move(depthTestedMesh)),
      alwaysVisibleMesh(std::move(alwaysVisibleMesh)) {}

void DebugRenderer::DrawLine(const math::Vec3& start, const math::Vec3& end,
                             const math::Vec3& color, DebugDepth depth) {
    debug_geometry::AppendLine(batch(depth), start, end, color);
}

void DebugRenderer::DrawBox(const Bounds& localBounds, const math::Mat4& transform,
                            const math::Vec3& color, DebugDepth depth) {
    debug_geometry::AppendBox(batch(depth), {localBounds.minimum, localBounds.maximum}, transform,
                              color);
}

void DebugRenderer::DrawCircle(const math::Vec3& localCenter, float radius,
                               const math::Mat4& transform, const math::Vec3& color,
                               DebugDepth depth) {
    debug_geometry::AppendCircle(batch(depth), localCenter, radius, transform, color);
}

void DebugRenderer::Render() {
    shader.Use();
    drawBatch(depthTestedMesh, batch(DebugDepth::Tested), true);
    drawBatch(alwaysVisibleMesh, batch(DebugDepth::AlwaysVisible), false);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glLineWidth(1.0F);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);

    for (auto& vertices : batches) {
        vertices.clear();
    }
}

std::vector<MeshVertex>& DebugRenderer::batch(DebugDepth depth) {
    return batches[debug_geometry::BatchIndex(depth)];
}

void DebugRenderer::drawBatch(Mesh& mesh, std::vector<MeshVertex>& vertices, bool depthTested) {
    if (vertices.empty()) {
        return;
    }

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    if (depthTested) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    mesh.UpdateVertices(vertices);
    mesh.Draw();
}
