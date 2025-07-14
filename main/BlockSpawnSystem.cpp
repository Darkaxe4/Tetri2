#include "Includes.hpp"

void BlockSpawnSystem::on_load()
{
    auto& registry = Game::get_scene_manager().get_current_scene()->get_registry();
    if (registry.view<Tetramino>().empty())
        refill_and_shuffle();
}

void BlockSpawnSystem::update(entt::registry& registry, sf::Time dt)
{

	if (registry.view<Tetramino>().empty() and not registry.view<Grid>().empty())
	{
        auto grid_entity = registry.view<Grid>().begin();
        const auto& grid = registry.get<Grid>(*grid_entity);
        sf::Vector2i dismensions = { (int)grid.width(), (int)grid.height()};

        generate_tetramino(registry, next_tetramino(), sf::Vector2i{ dismensions.x / 2, 0 });
	}
	
}

void BlockSpawnSystem::on_unload()
{
}


void BlockSpawnSystem::refill_and_shuffle() {
    std::iota(bucket.begin(), bucket.end(), 0); // Fill with 0..6
    
    std::shuffle(bucket.begin(), bucket.end(), *Game::get_random_generator());
    current_tetramino = 0;
}

const int* BlockSpawnSystem::next_tetramino() {
    if (current_tetramino >= bucket.size()) {
        refill_and_shuffle();
    }
    return TetraminoTypes[bucket[current_tetramino++]];
}

void BlockSpawnSystem::generate_tetramino(entt::registry& registry, const int* tetramino, sf::Vector2i position)
{
    auto tetramino_type = std::rand() % 7;
    auto tetramino_color = std::rand() % 4;

    auto entity = registry.create();
    registry.emplace<Tetramino>(entity, static_cast<size_t>(entity));

    auto block_palette_texture = Game::get_resource_manager().get_texture("block_atlas");
    const auto& texture_dims = block_palette_texture->getSize();
    auto block_palette_size = sf::Vector2i{ (int)texture_dims.x / (int)texture_dims.y, 1 };
    
    for (auto i = size_t{ 0 }; i < 4; i++)
    {
        auto block = registry.create();
        auto& block_component = registry.emplace<Block>(
            block,
                static_cast<size_t>(entity),
                static_cast<Color>(tetramino_color)
            );
        registry.emplace<GridPosition>(
            block,
            position.x + tetramino[i] % 2, position.y + tetramino[i] / 2
            );
        registry.emplace<TiledRenderComponent>(
            block,
            block_palette_texture,
            sf::IntRect{ {tetramino_color * (int)texture_dims.y, 0}, {(int)texture_dims.y, (int)texture_dims.y} },
            block_palette_size,
            size_t{ 10 }
        );
        auto block_position = sf::Vector2f(registry.get<GridPosition>(block).position) * (float)texture_dims.y;

        registry.patch<TiledRenderComponent>(block,
            [&block_position](TiledRenderComponent& component) {
                component.states.transform.translate(block_position);
            }
        );

        registry.emplace<GravityAffected>(block);
    }
}
