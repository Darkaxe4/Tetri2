#include "Includes.hpp"


Field::Field():
	active(), next()
{
	cells.clear();
	cells.resize(size.y);
	for (auto y = 0; y < size.y; y++)
	{
		cells[y] = std::vector<int>(size.x, -1);
	}

}


boundCheckResult Field::check_bounds(Tetramino* active, bool isVerticalTransform)
{
	for (auto block : active->blocks)
	{
		if (block.x >= size.x || block.x < 0 || block.y < 0)
			return BOUND;
		if (block.y >= size.y)
			return FILLEDCELL;
		if (cells[block.y][block.x] != -1)
			return isVerticalTransform ? FILLEDCELL : BOUND;
	}	
	return SUCCESS;
}


int Field::solidify(Tetramino* tetramino)
{
	for (auto block : tetramino->blocks)
	{
		cells[block.y][block.x] = tetramino->color;
	}
	
	return clear_full_rows();
}

void Field::swapRows(int lowerRowIndex)
{

	while (lowerRowIndex != 0)
	{
		std::swap(cells[lowerRowIndex], cells[lowerRowIndex - 1]);
		lowerRowIndex--;
	}
	
}

const std::vector<std::vector<int>>& Field::get_cells()
{
	return cells;
}



int Field::clear_full_rows()
{
	auto result = 0;

	for (auto i = 0; i < size.y; i++)
	{
		auto isFull = true;
		for (auto cell : cells[i])
		{
			if (cell == -1)
			{
				isFull = false;
				break;
			}
		}
		if (isFull)
		{
			cells[i].assign(size.x, -1);
			swapRows(i);
			result ++;
		}
	}

	return result;
}

void Field::clear()
{
	cells.clear();
	cells.resize(size.y);
	for (auto y = 0; y < size.y; y++)
	{
		cells[y] = std::vector<int>(size.x, -1);
	}
}

json& Field::to_json()
{
	auto data = json();
	data["cells"] = cells;
	return data;
}

void Field::from_json(json& json)
{
	cells = json["cells"];
}


FieldController::FieldController(Field& field):
	field(&field), active(&field.active), next(&field.next)
{
}

void FieldController::move_active(int dx, int dy)
{
	auto backup = new sf::Vector2i[4];

	for (auto i = 0; i < 4; i++)
		backup[i] = active->blocks[i];

	active->move(dx, dy);

	auto res = field->check_bounds(active, dy != 0);
	if (res != SUCCESS)
		for (auto i = 0; i < 4; i++)
			active->blocks[i] = backup[i];
	if (res == FILLEDCELL)
	{
		field->solidify(active);
		active = next;
		next->generate_tetramino();
	}
}

void FieldController::rotate_active()
{
	auto backup = new sf::Vector2i[4];
	for (auto i = 0; i < 4; i++)
		backup[i] = active->blocks[i];

	active->rotate();

	auto res = field->check_bounds(active, false);
	if (res != SUCCESS)
		for (auto i = 0; i < 4; i++)
			active->blocks[i] = backup[i];
	if (res == FILLEDCELL)
	{
		field->solidify(active);
		active = next;
		next->generate_tetramino();
	}
}

void FieldView::prerender_field()
{
	fieldPrerender.clear(sf::Color::Transparent);
	auto const& cells = field->get_cells();
	auto offset = sf::Vector2f{};
	for (auto row = size_t{0}; row < size.y; row++)
	{
		offset.y = brickSize.y * row;
		for (auto column = size_t{ 0 }; column < size.x; column++)
		{
			if (cells[row][column] == -1)
				continue;
			offset.x = brickSize.x * column;
			brick.setPosition(margin + offset);
			brick.setTextureRect(sf::IntRect{0 + cells[row][column] * brickSize.x, 0, brickSize.x, brickSize.y});
			fieldPrerender.draw(brick);
		}
	}
	fieldPrerender.display();
}

const sf::RenderTexture& FieldView::prerender_tetramino(const Tetramino& tetramino)
{
	tetraminoPrerender.clear(sf::Color::Transparent);
	brick.setTextureRect(sf::IntRect{ 0 + tetramino.color * brickSize.x, 0, brickSize.x, brickSize.y });
	for (auto i = size_t{ 0 }; i < 4; i++)
	{
		brick.setPosition(brickSize.x * (tetramino.blocks[i].x), brickSize.y * (tetramino.blocks[i].y));
		tetraminoPrerender.draw(brick);
	}
	tetraminoPrerender.display();
	return tetraminoPrerender;
}

FieldView::FieldView(Field& field):
	field(&field), brick(), fieldPrerender(),
	tetraminoPrerender(),
	active(&field.active), next(&field.next)
{
	fieldSprite.setPosition(margin);
	fieldPrerender.create(brickSize.x * size.x, brickSize.y * size.y);
	tetraminoPrerender.create(brickSize.x * 2u, brickSize.y * 4u);
}

void FieldView::set_back_texture(std::string_view path)
{
		backgroundTexture.loadFromFile(path.data());
		backgroundSprite.setTexture(backgroundTexture);
}

void FieldView::set_palette(std::string_view path)
{
		brickPaletteTexture.loadFromFile(path.data());
		brick.setTexture(brickPaletteTexture);
}

void FieldView::update_active(const sf::Vector2f& offset, float rotation)
{
	tetraminoSprite.move(offset);
	tetraminoSprite.rotate(rotation);
}

void FieldView::update()
{
	prerender_field();
	fieldTexture = fieldPrerender.getTexture();
	tetraminoSprite.setTexture(tetraminoPrerender.getTexture());
}

void FieldView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(backgroundSprite, states);
	auto shift = sf::Transform();
	shift.translate(margin);
	states.transform *= shift;
	target.draw(fieldSprite, states);

	target.draw(tetraminoSprite, states);


}
