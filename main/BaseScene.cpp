#include "Includes.hpp"

BaseScene::BaseScene(int index):
	index(index), render_queue(),
	initialized(false)
{
	gui = tgui::Group::create();
}

// inserts drawable in render_queue according to its z_index
void BaseScene::add_drawable(const sf::Drawable& drawable, int z_index)
{
	if (z_index >= render_queue.size())
		render_queue.push_back(RenderObject{ &drawable, z_index });
	else
	{
		auto place = render_queue.begin();
		for (;place->z_index < z_index; place++);
		render_queue.insert(place, RenderObject{ &drawable, z_index });
	}
}

void BaseScene::render(sf::RenderTarget& target, const sf::RenderStates& states)
{
	for (auto const& x : render_queue)
	{
		target.draw(*x.drawable, states);
	}
}

BaseScene::~BaseScene()
{
	for (auto& [key, value] : sprite_registry)
	{
		delete value;
	}
}
