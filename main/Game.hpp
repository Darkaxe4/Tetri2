#pragma once
class Game
{
private:
	// managers
	static SoundManager* sound_manager;
	static InputManager* input_manager;
	static SceneManager* scene_manager;
	static ResourceManager* resource_manager;
	static SystemManager* system_manager;

	// settings
	static Settings* settings;
	
	// JSON loader
	static JSONFileIO* json_io;

	// utilities
	static sf::RenderWindow* game_window;
	static sf::Clock* main_clock;
	
	// random
	static std::mt19937* random_generator;

	// letterboxing
	static const sf::View virtual_view;

public:
	static inline auto& get_json_io() { return *json_io; }
	static inline auto& get_input_manager() { return *input_manager; }
	static inline auto& get_resource_manager() { return *resource_manager; }
	static inline auto& get_scene_manager() { return *scene_manager; }
	static inline auto& get_sound_manager() { return *sound_manager; }
	static inline auto& get_system_manager() { return *system_manager; }

	static inline auto& get_settings() { return *settings; }
	
	static void init();
	static inline auto get_window() { return game_window; }
	static inline auto get_random_generator() { return random_generator; }
	static void end_main_loop();
	static void main_loop();

	static void cleanup();
};

