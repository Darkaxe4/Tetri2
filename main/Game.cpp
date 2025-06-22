#include "Includes.hpp"
SoundManager* Game::sound_manager = nullptr;
InputManager* Game::input_manager = nullptr;
SceneManager* Game::scene_manager = nullptr;
ResourceManager* Game::resource_manager = nullptr;
SystemManager* Game::system_manager = nullptr;

Settings* Game::settings = nullptr;

sf::RenderWindow* Game::game_window = nullptr;
sf::Clock* Game::main_clock = nullptr;


void Game::init()
{
    std::srand(std::time({}));

    sound_manager = new SoundManager();
    input_manager = new InputManager();
    scene_manager = new SceneManager();
    resource_manager = new ResourceManager();
    system_manager = new SystemManager();

    game_window = new sf::RenderWindow(sf::VideoMode({ 1920, 1000 }), "Tetri2");
    main_clock = new sf::Clock{};
}


void Game::end_main_loop()
{
    game_window->close();
}

void Game::main_loop()
{
    while (game_window->isOpen())
    {
        auto dt = main_clock->getElapsedTime();
        main_clock->restart();
        while (const std::optional event = game_window->pollEvent()) {

            scene_manager->get_gui()->handleEvent(*event);
            
            if (event->is<sf::Event::Closed>())
                game_window->close();
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({ 0, 0 }, sf::Vector2f{ resized->size });
                game_window->setView(sf::View(visibleArea));
            }
            if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
            {
                // process input via InputManager
                input_manager->process_input(*event);
            }
        }

        scene_manager->get_current_scene()->update(dt);

        game_window->clear();

        system_manager->update_systems(dt);

        // render current scene
        scene_manager->get_current_scene()->render(*game_window, sf::RenderStates{});

        // render GUI
        scene_manager->get_gui()->draw();
        
        AK::SoundEngine::RenderAudio();
        game_window->display();
    }
}

void Game::cleanup()
{
    delete sound_manager;
    delete input_manager;
    delete scene_manager;
    delete resource_manager;
    delete system_manager;

    delete game_window;
    delete main_clock;
}

