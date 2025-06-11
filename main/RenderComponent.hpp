#pragma once
#include "SFML/Graphics.hpp"

struct RenderComponent
{
	sf::Texture* texture;
	sf::IntRect texture_rect;
	sf::RenderStates states;
};