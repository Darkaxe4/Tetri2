#include "Includes.hpp"

void SystemManager::load_systems()
{
	for (auto& system : systems)
	{
		system->on_load();
	}
}

void SystemManager::register_system(BaseSystem* system)
{
	systems.push_back(system);
}

void SystemManager::update_systems(sf::Time dt)
{
	auto& registry = Game::get_scene_manager().get_current_scene()->get_registry();
	for (auto& system : systems)
	{
		system->update(registry, dt);
	}
}

SystemManager::~SystemManager()
{
	for (auto& system : systems)
	{
		delete system;
	}
}
