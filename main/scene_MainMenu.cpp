#include "Includes.hpp"

void MainMenu::bind_input()
{
    Game::get_input_manager().subscribe("back", [this] {this->back_handler();});
}

MainMenu::MainMenu():
    BaseScene(0),
    background(new sf::Texture()),
    gui_atlas(new sf::Texture()),
    state(new MainState)
{
    
}

void MainMenu::set_state(BaseMainMenuState* new_state)
{
    if (state)
    {
        state->on_exit();
        delete state;
    }
    state = new_state;
    state->on_enter();
}

bool MainMenu::load()
{

    if (initialized)
    {
        bind_input();
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
    gui->get<tgui::Button>("Settings")->onPress([this] {
        set_state(new SettingsState{});
        });
    gui->get<tgui::Button>("Quit")->onPress([] {Game::end_main_loop();});

    gui->get<tgui::ToggleButton>("Video")->onToggle([this](bool checked) {
        auto other = {
            gui->get<tgui::ToggleButton>("Sound"),
            gui->get<tgui::ToggleButton>("Language")
        };

        gui->get<tgui::Panel>("Video_items")->setVisible(checked);

        if (checked) for (auto& x : other) x->setDown(false);
        });

    gui->get<tgui::ToggleButton>("Sound")->onToggle([this](bool checked) {
        auto other = {
            gui->get<tgui::ToggleButton>("Video"),
            gui->get<tgui::ToggleButton>("Language")
        };

        gui->get<tgui::Panel>("Sound_items")->setVisible(checked);

        if (checked) for (auto& x : other) x->setDown(false);
        });

    bind_input();

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

void MainState::on_enter()
{
}

void MainState::process_back(MainMenu* ptr)
{
}

void MainState::on_exit()
{
}

void SettingsState::on_enter()
{
    Game::get_scene_manager().get_gui()->get<tgui::Group>("settings")->setVisible(true);
}

void SettingsState::process_back(MainMenu* ptr)
{
    ptr->set_state(new MainState{});
}

void SettingsState::on_exit()
{
    Game::get_scene_manager().get_gui()->get<tgui::Group>("settings")->setVisible(false);
}
