#pragma once

#include "glad/gl.h"
#include "math/mat4.hpp"
#include "math/vec3.hpp"
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

    void SetFloatUniform(const std::string& name, float value) const;
    void SetMat4Uniform(const std::string& name, const math::Mat4& value) const;
    void SetVec3Uniform(const std::string& name, const math::Vec3& value) const;

  private:
    bool checkShaderCompilation(GLuint shader, GLint type);
    bool checkProgramLink(GLuint program);
};
