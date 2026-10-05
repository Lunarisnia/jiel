#pragma once
#include "glad/gl.h"
#include "math/vec3.hpp"
#include <vector>
struct MeshData {
    std::vector<math::Vec3> vertice{};
    std::vector<GLuint> indice{};
};

class Mesh {
  private:
    GLuint vbo;
    GLuint vao;

    GLsizei indexCount;
    GLuint ebo;

  public:
    Mesh(const MeshData& data);

    void Draw();
};
