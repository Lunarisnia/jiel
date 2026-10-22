#include "game_object.hpp"
#include "ecs/component.hpp"
#include "ecs/renderable_component.hpp"

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

void GameObject::Render() {
    for (const auto& component : components) {
        if (auto* renderable = dynamic_cast<RenderableComponent*>(component.get())) {
            renderable->Render();
        }
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
