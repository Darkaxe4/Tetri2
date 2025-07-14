#pragma once
#include <SFML/Graphics.hpp>
#include "Tetramino.hpp"

struct GridPosition
{
	sf::Vector2i position;
	GridPosition() = delete;
	GridPosition(int x, int y):position(x, y) { }
};

struct Move
{
	sf::Vector2i delta;
	Move() = delete;
	Move(sf::Vector2i delta):delta(delta) { }
};

struct Block
{
	size_t tetramino_id;
	Color color;
};

struct Tetramino
{
	size_t id;
};

struct GravityAffected
{ };

struct Collision
{ };

struct Grid
{
	std::vector<std::vector<Block*>> grid;
	Grid() = delete;

	inline Grid(size_t x, size_t y):grid(){
		grid.resize(x);
		for (auto i = size_t{ 0 }; i < x; i++)
			grid[i].resize(y);
	}

	inline size_t height() const {
		return grid.empty() ? 0 : grid[0].size();
	}

	inline size_t width() const {
		return grid.size();
	}
};