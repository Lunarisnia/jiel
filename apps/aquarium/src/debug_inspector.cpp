#include "debug_inspector.hpp"

#include "game_object.hpp"

#include <imgui.h>

void DebugInspector::Draw(GameObject* object) {
    ImGui::Begin("Aquarium");
    ImGui::DragFloat3("Position", &object->transform->position.x, 0.01F, -1.0F, 1.0F);
    ImGui::DragFloat3("Scale", &object->transform->scale.x, 0.01F, 0.0F, 3.0F);
    ImGui::DragFloat3("Rotation", &object->transform->rotation.x, 1.0F, -180.0F, 180.0F);
    ImGui::End();
}
