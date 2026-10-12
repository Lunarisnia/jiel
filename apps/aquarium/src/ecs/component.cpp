#include "ecs/component.hpp"

#include <utility>

Component::Component(std::string id) : id(std::move(id)) {}

void Component::Init() {}

void Component::Update() {}
