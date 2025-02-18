#include "Includes.hpp"

Tetramino::Tetramino()
{
}

Tetramino::Tetramino(const int(&shape)[4])
{
	for (auto i = 0; i < 4; i++)
	{
		blocks[i].x = shape[i] % 2;
		blocks[i].y = shape[i] / 2;
	}
}

Tetramino::Tetramino(const int(&shape)[4], sf::Vector2i pos)
{
	for (auto i = 0; i < 4; i++)
	{
		blocks[i].x = pos.x + shape[i] % 2;
		blocks[i].y = pos.y + shape[i] / 2;
	}
}

void Tetramino::move(int dx, int dy)
{
	for (auto& block : blocks)
	{
		block.x += dx;
		block.y += dy;
	}
}

void Tetramino::rotate()
{
	auto origin = blocks[1];
	for (size_t i = 0; i < 4; i++)
	{
		auto dx = blocks[i].x - origin.x;
		auto dy = blocks[i].y - origin.y;
		blocks[i].x = origin.x - dy;
		blocks[i].y = origin.y + dx;
	}
}

Tetramino* Tetramino::generate_tetramino()
{
	auto type = std::rand() % 7;
	auto color = std::rand() % 5;

	auto result = new Tetramino(TetraminoTypes[type], sf::Vector2i{ 0, 0 });
	result->color = static_cast<Color>(color);
	return result;
}

