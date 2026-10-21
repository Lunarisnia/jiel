#pragma once

#include "math/vec3.hpp"

#include <cstdint>
#include <span>
#include <vector>

struct MeshVertex {
    math::Vec3 position{};
    math::Vec3 color{1.0F, 1.0F, 1.0F};
};

struct MeshData {
    std::vector<MeshVertex> vertices{};
    std::vector<std::uint32_t> indices{};
};

enum class MeshTopology {
    Triangles,
    Lines,
};

enum class MeshUsage {
    Static,
    Dynamic,
};

class Mesh {
  public:
    explicit Mesh(const MeshData& data, MeshTopology topology = MeshTopology::Triangles,
                  MeshUsage usage = MeshUsage::Static);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void UpdateVertices(std::span<const MeshVertex> vertices);
    void Draw() const;

  private:
    void destroy();

    unsigned int vertexBuffer = 0;
    unsigned int vertexArray = 0;
    unsigned int indexBuffer = 0;
    int vertexCount = 0;
    int indexCount = 0;
    MeshTopology topology = MeshTopology::Triangles;
    MeshUsage usage = MeshUsage::Static;
};
