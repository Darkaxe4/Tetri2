#pragma once
#include "entt.hpp"
#include "SFML/Graphics.hpp"

class BaseSystem
{
public:
	virtual void on_load() = 0;
	virtual void update(entt::registry& registry, sf::Time dt) = 0;
	virtual void on_unload() = 0;
};

