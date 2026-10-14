#include "ecs/transform_component.hpp"
#include "ecs/mesh_renderer_component.hpp"
#include "game_object.hpp"

void TransformComponent::Init() {
    meshRenderer = gameObject->GetComponent<MeshRendererComponent>();
}

void TransformComponent::Update() {
    if (meshRenderer) {
        meshRenderer->material->shader->SetMat4Uniform("model", Model());
    }
}
