#include "Includes.hpp"

Tetramino::Tetramino()
{
	generate_tetramino();
}

Tetramino::Tetramino(const int(&shape)[4]):
	color(Color::blue)
{
	for (auto i = 0; i < 4; i++)
	{
		blocks[i].x = shape[i] % 2;
		blocks[i].y = shape[i] / 2;
	}
}

Tetramino::Tetramino(const int(&shape)[4], sf::Vector2i pos) :
	color(Color::blue)
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

void Tetramino::generate_tetramino()
{
	auto type = std::rand() % 7;
	auto color = std::rand() % 5;
	std::cout << "gen " << type << color << std::endl;

	for (auto i = 0; i < 4; i++)
	{
		blocks[i].x = TetraminoTypes[type][i] % 2;
		blocks[i].y = TetraminoTypes[type][i] / 2;
	}
	this->color = static_cast<Color>(color);
}

