#include "Includes.hpp"

SceneManager::SceneManager():
	scenes({}),
	current_scene(nullptr),
	gui(nullptr)
{
}

void SceneManager::init_gui(sf::RenderTarget* render_window)
{
	if (not gui)
	{
		gui = new tgui::Gui{ *render_window };
	}
	else
		gui->setTarget(*render_window);
}

void SceneManager::register_scene(BaseScene* scene, std::string_view name)
{
	scenes[name.data()] = scene;
}

void SceneManager::load_scene(std::string_view scene_name)
{
	if (current_scene)
	{
		current_scene->unload();
	}
	if (auto search = scenes.find(scene_name.data()); search != scenes.end())
	{
		current_scene = search->second;
		current_scene->load();
		Game::get_system_manager().load_systems();

		if (auto scene_gui = gui->get<tgui::Group>(scene_name.data()))
			scene_gui->get<tgui::Group>(scene_name.data())->setVisible(true);
		else
			gui->add(current_scene->get_gui(), scene_name.data());
	}
	else
		throw std::format("Scene {} not found", scene_name.data());
}

SceneManager::~SceneManager()
{
	auto it = scenes.begin();
	while (it != scenes.end())
	{
		delete it->second;
		it++;
	}

	delete gui;
}
