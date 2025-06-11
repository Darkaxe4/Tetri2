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


boundCheckResult FieldController::check_bounds(Tetramino* active, bool isVerticalTransform)
{
	for (auto block : active->blocks)
	{
		if (block.x >= field->size.x || block.x < 0 || block.y < 0)
			return BOUND;
		if (block.y >= field->size.y)
			return FILLEDCELL;
		if (field->cells[block.y][block.x] != -1)
			return isVerticalTransform ? FILLEDCELL : BOUND;
	}	
	return SUCCESS;
}


int FieldController::solidify(Tetramino* tetramino)
{
	for (auto block : tetramino->blocks)
	{
		field->cells[block.y][block.x] = tetramino->color;
	}
	
	return clear_full_rows();
}

void FieldController::swapRows(int lowerRowIndex)
{

	while (lowerRowIndex != 0)
	{
		std::swap(field->cells[lowerRowIndex], field->cells[lowerRowIndex - 1]);
		lowerRowIndex--;
	}
	
}

const std::vector<std::vector<int>>& FieldController::get_cells()
{
	return field->cells;
}



int FieldController::clear_full_rows()
{
	auto result = 0;

	for (auto i = 0; i < field->size.y; i++)
	{
		auto isFull = true;
		for (auto cell : field->cells[i])
		{
			if (cell == -1)
			{
				isFull = false;
				break;
			}
		}
		if (isFull)
		{
			field->cells[i].assign(field->size.x, -1);
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

json Field::to_json() const
{
	auto data = json();
	data["cells"] = cells;
	return std::forward<json&>(data);
}

void Field::from_json(const json& json)
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

	auto res = check_bounds(active, dy != 0);
	if (res != SUCCESS)
		for (auto i = 0; i < 4; i++)
			active->blocks[i] = backup[i];
	if (res == FILLEDCELL)
	{
		solidify(active);
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

	auto res = check_bounds(active, false);
	if (res != SUCCESS)
		for (auto i = 0; i < 4; i++)
			active->blocks[i] = backup[i];
	if (res == FILLEDCELL)
	{
		solidify(active);
		active = next;
		next->generate_tetramino();
	}
}

void FieldView::prerender_field()
{
	fieldPrerender.clear(sf::Color::Transparent);
	auto const& cells = field->cells;
	auto offset = sf::Vector2f{};
	for (auto row = size_t{0}; row < size.y; row++)
	{
		offset.y = brickSize.y * row;
		for (auto column = size_t{ 0 }; column < size.x; column++)
		{
			if (cells[row][column] == -1)
				continue;
			offset.x = brickSize.x * column;
			brick->setPosition(margin + offset);
			brick->setTextureRect(sf::IntRect{ {0 + cells[row][column] * brickSize.x, 0}, {brickSize.x, brickSize.y} });
			fieldPrerender.draw(*brick);
		}
	}
	fieldPrerender.display();
}

const sf::RenderTexture& FieldView::prerender_tetramino(const Tetramino& tetramino)
{
	tetraminoPrerender.clear(sf::Color::Transparent);
	brick->setTextureRect(sf::IntRect{ {0 + tetramino.color * brickSize.x, 0}, {brickSize.x, brickSize.y } });
	for (auto i = size_t{ 0 }; i < 4; i++)
	{
		brick->setPosition({ float(brickSize.x) * (tetramino.blocks[i].x), float(brickSize.y) * (tetramino.blocks[i].y) });
		tetraminoPrerender.draw(*brick);
	}
	tetraminoPrerender.display();
	return tetraminoPrerender;
}

FieldView::FieldView(Field& field) :
	field(&field),
	active(&field.active), next(&field.next),
	tetraminoPrerender(),
	fieldPrerender()
{
	fieldPrerender.resize({ brickSize.x * size.x, brickSize.y * size.y });
	tetraminoPrerender.resize({ brickSize.x * 2u, brickSize.y * 4u });

	fieldSprite = new sf::Sprite(fieldPrerender.getTexture());
	fieldSprite->setPosition(margin);

	tetraminoSprite = new sf::Sprite(tetraminoPrerender.getTexture());

}

void FieldView::set_back_texture(std::string_view path)
{
		backgroundTexture.loadFromFile(path.data());
		backgroundTexture.setRepeated(true);
		backgroundSprite = new sf::Sprite(backgroundTexture);
		auto bgts = backgroundTexture.getSize();
		backgroundSprite->setTextureRect({ {0, 0}, {int(size.x * bgts.x / 4), int(size.y * bgts.y / 4)} });
}

void FieldView::set_palette(std::string_view path)
{
		brickPaletteTexture.loadFromFile(path.data());
		brick = new sf::Sprite(brickPaletteTexture);
}

void FieldView::update_active(const sf::Vector2f& offset, float rotation)
{
	tetraminoSprite->move(offset);
	tetraminoSprite->rotate(sf::degrees(rotation));
}

void FieldView::update()
{
	prerender_field();
	fieldTexture = fieldPrerender.getTexture();
	tetraminoSprite->setTexture(tetraminoPrerender.getTexture());
}

void FieldView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*backgroundSprite, states);
	auto shift = sf::Transform();
	shift.translate(margin);
	states.transform *= shift;
	target.draw(*fieldSprite, states);

	shift = sf::Transform::Identity;
	auto active_pos = sf::Vector2i{ active->blocks[0].x * brickSize.x, active->blocks[0].y * brickSize.y };
	shift.translate(sf::Vector2f{ float(active_pos.x), float(active_pos.y) });
	states.transform *= shift;
	target.draw(*tetraminoSprite, states);


}
