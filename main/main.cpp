#include "Includes.hpp"

enum class GameState
{
    Running,
    Paused,
    Gameover
};

int main()
{
    std::srand(std::time(0));
    auto mode = sf::VideoMode(1920u, 1020u);
    auto window = sf::RenderWindow(mode, "Tetri2");
    
    auto tf = Field();
    auto tf_controller = FieldController(tf);
    auto tf_view = FieldView(tf);
    tf_view.set_back_texture(AssetPath + "/Textures/Field.png");
    tf_view.set_palette(AssetPath + "/Textures/BlockAtlas.png");
    tf_view.setPosition(200, 10);
    tf_view.prerender_tetramino(tf.get_active());
    tf_view.update();
    auto const delay = 1.f;
    auto timer = 0.f;
    auto globalClock = sf::Clock();
    while (window.isOpen())
    {
        auto dt = globalClock.getElapsedTime().asSeconds();
        timer += dt;
        globalClock.restart();
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        if (timer >= delay)
        {
            tf_controller.move_active(0, 1);
            tf_view.update_active({0.f, 32.f});
            timer = 0.f;
        }

        window.clear();

        window.draw(tf_view);

        window.display();
    }
	return 0;
}




