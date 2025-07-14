#pragma once
class BlockSpawnSystem :
    public BaseSystem
{
private:
    std::array<size_t, 7> bucket;
    size_t current_tetramino = 0;

    void refill_and_shuffle();
    const int* next_tetramino();
    void generate_tetramino(entt::registry& registry, const int* tetramino, sf::Vector2i position);
public:
    // Inherited via BaseSystem
    void on_load() override;
    void update(entt::registry& registry, sf::Time dt) override;
    void on_unload() override;
};

