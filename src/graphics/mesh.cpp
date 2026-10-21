#include "graphics/mesh.hpp"

#include <glad/gl.h>

#include <cstddef>
#include <utility>

namespace {
GLenum ToOpenGlTopology(MeshTopology topology) {
    return topology == MeshTopology::Lines ? GL_LINES : GL_TRIANGLES;
}

GLenum ToOpenGlUsage(MeshUsage usage) {
    return usage == MeshUsage::Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
}
} // namespace

Mesh::Mesh(const MeshData& data, MeshTopology topology, MeshUsage usage)
    : vertexCount(static_cast<int>(data.vertices.size())),
      indexCount(static_cast<int>(data.indices.size())), topology(topology), usage(usage) {
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(data.vertices.size() * sizeof(MeshVertex)),
                 data.vertices.data(), ToOpenGlUsage(usage));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex),
                          reinterpret_cast<void*>(offsetof(MeshVertex, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex),
                          reinterpret_cast<void*>(offsetof(MeshVertex, color)));

    if (!data.indices.empty()) {
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     static_cast<GLsizeiptr>(data.indices.size() * sizeof(std::uint32_t)),
                     data.indices.data(), ToOpenGlUsage(usage));
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
    destroy();
}

Mesh::Mesh(Mesh&& other) noexcept
    : vertexBuffer(std::exchange(other.vertexBuffer, 0)),
      vertexArray(std::exchange(other.vertexArray, 0)),
      indexBuffer(std::exchange(other.indexBuffer, 0)),
      vertexCount(std::exchange(other.vertexCount, 0)),
      indexCount(std::exchange(other.indexCount, 0)), topology(other.topology), usage(other.usage) {
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    destroy();
    vertexBuffer = std::exchange(other.vertexBuffer, 0);
    vertexArray = std::exchange(other.vertexArray, 0);
    indexBuffer = std::exchange(other.indexBuffer, 0);
    vertexCount = std::exchange(other.vertexCount, 0);
    indexCount = std::exchange(other.indexCount, 0);
    topology = other.topology;
    usage = other.usage;
    return *this;
}

void Mesh::UpdateVertices(std::span<const MeshVertex> vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size_bytes()), vertices.data(),
                 ToOpenGlUsage(usage));
    vertexCount = static_cast<int>(vertices.size());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Draw() const {
    if (vertexCount == 0 && indexCount == 0) {
        return;
    }

    glBindVertexArray(vertexArray);
    if (indexCount > 0) {
        glDrawElements(ToOpenGlTopology(topology), indexCount, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(ToOpenGlTopology(topology), 0, vertexCount);
    }
}

void Mesh::destroy() {
    if (indexBuffer != 0) {
        glDeleteBuffers(1, &indexBuffer);
        indexBuffer = 0;
    }
    if (vertexBuffer != 0) {
        glDeleteBuffers(1, &vertexBuffer);
        vertexBuffer = 0;
    }
    if (vertexArray != 0) {
        glDeleteVertexArrays(1, &vertexArray);
        vertexArray = 0;
    }
}
