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
    Game::get_input_manager().bind_key(sf::Keyboard::Key::Escape, "back");

    // initialize gui handler
    Game::get_scene_manager().init_gui(Game::get_window());

    // register scenes
    Game::get_scene_manager().register_scene(new MainMenu(), menu_scene);
    Game::get_scene_manager().register_scene(new Gameplay(), gameplay_scene);
    
    Game::get_system_manager().register_system(new RenderSystem());
    Game::get_system_manager().register_system(new PhysicsSystem());
    Game::get_system_manager().register_system(new BlockSpawnSystem());

    Game::get_sound_manager().load_soundbank(L"Mesopotamia_tracks.bnk");

    Game::get_scene_manager().load_scene(menu_scene);

    Game::main_loop();
    Game::cleanup();

	return 0;
}




