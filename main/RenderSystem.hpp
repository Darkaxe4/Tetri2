#pragma once

class RenderSystem: public BaseSystem
{
private:
    
public:

    RenderSystem();

    // Inherited via BaseSystem
    void on_load() override;

    void update(entt::registry& registry, sf::Time dt) override;

    void on_unload() override;

};


void on_render_component_added(entt::registry& registry, entt::entity entity);
void on_tiled_render_component_added(entt::registry& registry, entt::entity entity);