#pragma once

enum Color
{
	yellow = 0,
	green = 1,
	red = 2,
	blue = 3,
	//pink = 4,
};

const int TetraminoTypes[7][4] =
{
	0, 2, 3, 5, //S
	1, 3, 2, 4, //Z
	1, 3, 5, 4, //J
	0, 2, 4, 5, //L
	0, 2, 4, 6, //I
	0, 1, 3, 2, //O
	1, 3, 2, 5, //T
};

struct Tetramino
{
	Color color;
	sf::Vector2i blocks[4] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };

	Tetramino();

	Tetramino(const int (&shape)[4]);
	Tetramino(const int(&shape)[4], sf::Vector2i startPos);
	void move(int dx, int dy);
	void rotate();

	void generate_tetramino();
};