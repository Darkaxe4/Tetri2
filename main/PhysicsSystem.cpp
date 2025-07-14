#include "Includes.hpp"


void PhysicsSystem::on_load()
{
}

void PhysicsSystem::update(entt::registry& registry, sf::Time dt)
{
	update_gravity(registry, dt);
	process_collisions(registry, dt);
}

void PhysicsSystem::update_gravity(entt::registry& registry, sf::Time dt)
{
	auto view = registry.view<GravityAffected, GridPosition>();
	for (auto entity : view) {
		auto& grid_position = view.get<GridPosition>(entity);
		grid_position.position.y += 1;
	}
}

void PhysicsSystem::process_collisions(entt::registry& registry, sf::Time dt)
{
}

void PhysicsSystem::on_unload()
{
}
