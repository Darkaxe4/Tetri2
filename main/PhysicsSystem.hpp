#pragma once

class BaseSystem;

class PhysicsSystem: public BaseSystem
{
public:
    // Inherited via BaseSystem
    void on_load() override;
    void update(entt::registry& registry, sf::Time dt) override;

    void update_gravity(entt::registry& registry, sf::Time dt);
    void process_collisions(entt::registry& registry, sf::Time dt);
    void on_unload() override;
};