#include "ecs/mesh_renderer_component.hpp"
#include "game_object.hpp"

void MeshRendererComponent::Render() {
    if (!mesh || !material || !material->shader || !gameObject || !gameObject->transform) {
        return;
    }

    material->Bind();
    material->shader->SetMat4Uniform("model", gameObject->transform->Model());
    mesh->Draw();
}
