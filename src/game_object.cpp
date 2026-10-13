#include "game_object.hpp"
#include "ecs/component.hpp"

GameObject::GameObject() : transform(std::make_shared<TransformComponent>()) {
    AddComponent(transform);
}

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

    newComponent->gameObject = this;
    components.emplace_back(newComponent);
}
