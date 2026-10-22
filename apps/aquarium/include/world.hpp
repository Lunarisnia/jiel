#pragma once

#include "game_object.hpp"
#include <memory>
#include <vector>
class World {
  private:
    unsigned int nextObjectId = 1;

  public:
    std::vector<std::shared_ptr<GameObject>> GameObjects;

  public:
    World();

    void Init();
    void Update();
    void Render();

    void AddGameObject(std::shared_ptr<GameObject> gameObject);
};
