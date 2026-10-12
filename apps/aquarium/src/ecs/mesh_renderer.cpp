#include "ecs/mesh_renderer.hpp"

void MeshRenderer::Init() {}

void MeshRenderer::Update() {
    if (!mesh || !material) {
        return;
    }

    material->Bind();
    mesh->Draw();
}
