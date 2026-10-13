#include "ecs/mesh_renderer_component.hpp"

void MeshRendererComponent::Init() {}

void MeshRendererComponent::Update() {
    if (!mesh || !material) {
        return;
    }

    material->Bind();
    mesh->Draw();
}
