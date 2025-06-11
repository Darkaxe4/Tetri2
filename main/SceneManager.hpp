#pragma once

class SceneManager
{
private:
	std::map<std::string, BaseScene*> scenes;
	BaseScene* current_scene;
	tgui::Gui* gui;
public:
	SceneManager();

	void init_gui(sf::RenderTarget* render_window);
	void register_scene(BaseScene* scene, std::string_view name);
	void load_scene(std::string_view scene_name);

	inline auto get_current_scene() { return current_scene; }
	inline auto get_gui() { return gui; }

	~SceneManager();
};

