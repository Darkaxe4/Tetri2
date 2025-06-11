#pragma once

#include "SFML/Graphics.hpp"

struct MovementComponent
{
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
};