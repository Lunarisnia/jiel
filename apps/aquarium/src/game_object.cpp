#include "game_object.hpp"

void GameObject::Init() {
    for (auto c : components) {
        c->Init();
    }
}

void GameObject::Update() {
    for (auto c : components) {
        c->Update();
    }
}

void GameObject::AddComponent(std::shared_ptr<Component> newComponent) {
    for (auto c : components) {
        if (c->id == newComponent->id) {
            return;
        }
    }

    components.emplace_back(newComponent);
}
