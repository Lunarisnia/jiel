#include "graphics/material.hpp"

void Material::Bind() const {
    if (shader) {
        shader->Use();
    }
}
