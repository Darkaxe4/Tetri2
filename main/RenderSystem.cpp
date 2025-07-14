#include "Includes.hpp"

void on_tiled_render_component_added(entt::registry& registry, entt::entity entity)
{
	auto& render_component = registry.get<TiledRenderComponent>(entity);
	Game::get_scene_manager().get_current_scene()->add_drawable(*render_component.sprite, render_component.z_layer, render_component.states);
}

void on_render_component_added(entt::registry& registry, entt::entity entity)
{
	auto& render_component = registry.get<RenderComponent>(entity);
	Game::get_scene_manager().get_current_scene()->add_drawable(*render_component.sprite, render_component.z_layer, render_component.states);
}

RenderSystem::RenderSystem()
{
}

void RenderSystem::on_load()
{
	auto scene = Game::get_scene_manager().get_current_scene();
	auto& registry = scene->get_registry();

	registry.on_construct<RenderComponent>().connect<&on_render_component_added>();
	registry.on_construct<TiledRenderComponent>().connect<&on_tiled_render_component_added>();
	
}

void RenderSystem::update(entt::registry& registry, sf::Time dt)
{
	
}

void RenderSystem::on_unload()
{
}
