#pragma once
class Game
{
private:
	// managers
	static SoundManager* sound_manager;
	static InputManager* input_manager;
	static SceneManager* scene_manager;
	static ResourceManager* resource_manager;

	
	// InputManager input_manager;
	static sf::RenderWindow* game_window;
	static sf::Clock* main_clock;
	

public:
	static inline auto& get_sound_manager() { return *sound_manager; }
	static inline auto& get_input_manager() { return *input_manager; }
	static inline auto& get_scene_manager() { return *scene_manager; }
	static inline auto& get_resource_manager() { return *resource_manager; }
	
	static void init();
	static inline auto get_window() { return game_window; }
	static void end_main_loop();
	static void main_loop();

	static void cleanup();
};

