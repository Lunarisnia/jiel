#include "world.hpp"
#include "game_object.hpp"
#include <memory>

World::World() {}

void World::Init() {
    for (auto& g : GameObjects) {
        g->Init();
    }
}

void World::Update() {
    for (auto& g : GameObjects) {
        g->Update();
    }
}

void World::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    GameObjects.emplace_back(gameObject);
}
