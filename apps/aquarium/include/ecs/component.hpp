#pragma once

#include <string>

class Component {
  public:
    const std::string id;

    explicit Component(std::string id);
    virtual ~Component() = default;

  public:
    virtual void Init();
    virtual void Update();
};
