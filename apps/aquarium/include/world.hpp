#pragma once

#include "game_object.hpp"
#include <memory>
#include <vector>
class World {
  public:
    std::vector<std::shared_ptr<GameObject>> GameObjects;

  public:
    World();

    void Init();
    void Update();

    void AddGameObject(std::shared_ptr<GameObject> gameObject);
};
