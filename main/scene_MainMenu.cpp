#include "Includes.hpp"

MainMenu::MainMenu():
    BaseScene(0),
    background(new sf::Texture()),
    gui_atlas(new sf::Texture())
{
    
}

bool MainMenu::load()
{
    if (initialized)
    {
        return true;
    }

    if (not background->loadFromFile(AssetPath + "\\Textures\\PauseBackground.png"))
        return false;

    auto background_sprite = new sf::Sprite(*background);
    sprite_registry.emplace(std::make_pair("background", background_sprite));
    add_drawable(*background_sprite, 0);
    
    // gui initialization
    gui->loadWidgetsFromFile(AssetPath + "\\GUI_forms\\" + menu_scene + ".txt");
    gui->get<tgui::Button>("Play")->onPress([] {
        Game::get_scene_manager().load_scene(gameplay_scene);
        });
    gui->get<tgui::Button>("Quit")->onPress([] {Game::end_main_loop();});

    initialized = true;

    return true;
}

bool MainMenu::save()
{
    return false;
}

void MainMenu::unload()
{
    gui->get<tgui::Group>(menu_scene)->setVisible(false);
}

void MainMenu::update(sf::Time elapsed_time)
{

}


