#include "Includes.hpp"

BaseScene::BaseScene(int index):
	index(index), render_queue(),
	initialized(false)
{
	gui = tgui::Group::create();
}

// inserts drawable in render_queue according to its z_index
void BaseScene::add_drawable(const sf::Drawable& drawable, int z_index, const sf::RenderStates& states)
{
	if (z_index >= render_queue.size())
		render_queue.emplace_back(&drawable, &states, z_index);
	else
	{
		auto place = render_queue.begin();
		for (;place->z_index < z_index; place++);
		render_queue.emplace(place, &drawable, &states, z_index );
	}
}

void BaseScene::remove_drawable(const sf::Drawable& drawable)
{
	for (auto it = render_queue.begin(); it != render_queue.end(); it++)
	{
		if (it->drawable == &drawable)
		{
			render_queue.erase(it);
			break;
		}
	}
}

void BaseScene::render(sf::RenderTarget& target, const sf::RenderStates& states)
{
	for (auto const& x : render_queue)
	{
		// Combine render states manually:
		sf::RenderStates combined;
		combined.blendMode = states.blendMode; // assume base wins
		combined.transform = states.transform * x.states->transform;
		combined.texture = x.states->texture ? x.states->texture : states.texture;
		combined.shader = x.states->shader ? x.states->shader : states.shader;

		target.draw(*x.drawable, *x.states);
	}
}

BaseScene::~BaseScene()
{
	for (auto& [key, value] : sprite_registry)
	{
		delete value;
	}
}
