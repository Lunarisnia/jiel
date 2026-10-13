#pragma once

#include <string>

class GameObject;

class Component {
  public:
    const std::string id;
    GameObject* gameObject = nullptr;

    explicit Component(std::string id);
    virtual ~Component() = default;

  public:
    virtual void Init();
    virtual void Update();
};
