#pragma once

#include "glad/gl.h"
#include <string>
#include <vector>
class Shader {
  private:
    GLuint program;

    std::vector<GLuint> shaders{};

  public:
    Shader();

    void Add(std::string source, GLint shaderType);
    void Compile();
    void Use();

  private:
    bool checkShaderCompilation(GLuint shader, GLint type);
    bool checkProgramLink(GLuint program);
};
