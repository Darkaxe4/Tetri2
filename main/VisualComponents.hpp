#pragma once
#include "SFML/Graphics.hpp"

struct RenderComponent
{
	sf::Texture* texture;
	sf::Sprite* sprite;
	sf::RenderStates states;
	size_t z_layer;

	RenderComponent() = delete;
	RenderComponent(sf::Texture* texture) : 
	texture(texture), 
	sprite(new sf::Sprite{ *texture }),
	states(),
	z_layer(0)
	{}
	RenderComponent(sf::Texture* texture, size_t z_layer) :
		texture(texture),
		sprite(new sf::Sprite{ *texture }),
		states(),
		z_layer(z_layer)
	{
	}
	~RenderComponent()
	{
		delete sprite;
	}
};

struct TiledRenderComponent: public RenderComponent
{
	sf::IntRect rect;
	sf::Vector2i tile_grid;

	TiledRenderComponent() = delete;
	TiledRenderComponent(sf::Texture* texture) :
		RenderComponent(texture),
		rect(sf::IntRect({ 0, 0 }, sf::Vector2i{
			static_cast<int>(texture->getSize().x),
			static_cast<int>(texture->getSize().y)
		})),
		tile_grid(sf::Vector2i{ 1, 1 })
	{
		sprite->setTextureRect(rect);
	}

	TiledRenderComponent(sf::Texture* texture, sf::IntRect rect, sf::Vector2i tile_grid) :
		RenderComponent(texture),
		rect(rect),
		tile_grid(tile_grid)
	{
		sprite->setTextureRect(rect);
	}

	TiledRenderComponent(sf::Texture* texture, sf::IntRect rect, sf::Vector2i tile_grid, size_t z_layer) :
		RenderComponent(texture, z_layer),
		rect(rect),
		tile_grid(tile_grid)
	{
		sprite->setTextureRect(rect);
	}
};

struct AnimatedComponent: public RenderComponent
{
	sf::IntRect rect;
	sf::Vector2i tile_grid;
	int frame;
	int frameCount;
	float frameTime;
	float frameTimer;

	AnimatedComponent() = delete;
	AnimatedComponent(sf::Texture* texture) :
		RenderComponent(texture),
		rect(sf::IntRect({ 0, 0 }, sf::Vector2i{
			static_cast<int>(texture->getSize().x),
			static_cast<int>(texture->getSize().y)
			})),
		tile_grid(sf::Vector2i{ 1, 1 }),
		frame(0),
		frameCount(0),
		frameTime(0.1f),
		frameTimer(0.0f)
	{}

	AnimatedComponent(sf::Texture* texture, size_t z_layer) :
		RenderComponent(texture, z_layer),
		rect(sf::IntRect({ 0, 0 }, sf::Vector2i{
			static_cast<int>(texture->getSize().x),
			static_cast<int>(texture->getSize().y)
			})),
		tile_grid(sf::Vector2i{ 1, 1 }),
		frame(0),
		frameCount(0),
		frameTime(0.1f),
		frameTimer(0.0f)
	{
	}

};