#include "Includes.hpp"

enum class GameState
{
    Running,
    Paused,
    Gameover
};

int main()
{
    Game::init();

    // debug mappings - REMOVE LATER
    Game::get_input_manager().bind_key(sf::Keyboard::Key::Escape, "pause");

    // initialize gui handler
    Game::get_scene_manager().init_gui(Game::get_window());

    // register scenes
    Game::get_scene_manager().register_scene(new MainMenu(), menu_scene);
    Game::get_scene_manager().register_scene(new Gameplay(), gameplay_scene);
    
    Game::get_sound_manager().load_soundbank(L"Mesopotamia_tracks.bnk");

    Game::get_scene_manager().load_scene(menu_scene);

    Game::main_loop();
    Game::cleanup();

    JSONFileIO f{};
    Settings s{};
    s.from_json(f.read_json("settings.json"));

    std::cout << "settings read";

    f.write_json(s, "settings.json");

	return 0;
}




