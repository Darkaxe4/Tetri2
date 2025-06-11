#include "Includes.hpp"

void Gameplay::pause()
{
    static auto paused = false;
    paused = !paused;

    auto sound_action = (paused) ? AK::SoundEngine::AkActionOnEventType_Pause : AK::SoundEngine::AkActionOnEventType_Resume;
    AK::SoundEngine::ExecuteActionOnPlayingID(sound_action, current_track);

    auto pause_group = gui->get<tgui::Group>("pause");
    pause_group->setVisible(paused);
}

Gameplay::Gameplay() :
    BaseScene(1),
    background(new sf::Texture()),
    field(nullptr),
    field_controller(nullptr),
    field_view(nullptr),
    current_track(),
    tetramino_fall_delay(0.f)
{
}

bool Gameplay::load()
{
    if (initialized)
    {
        
        return true;
    }

    if (not background->loadFromFile(AssetPath + "\\Textures\\Background.png"))
        return false;

    auto background_sprite = new sf::Sprite(*background);
    sprite_registry.emplace(std::make_pair("background", background_sprite));
    add_drawable(*background_sprite, 0);

    // gui initialization
    gui->loadWidgetsFromFile(AssetPath + "\\GUI_forms\\" + gameplay_scene + ".txt");
    initialized = true;


    auto continue_btn = gui->get<tgui::Button>("Continue");
    auto back_to_menu_btn = gui->get<tgui::Button>("Back to menu");

    continue_btn->onPress([this] {this->pause();});
    back_to_menu_btn->onPress([] {Game::get_scene_manager().load_scene(menu_scene);});
    
    Game::get_input_manager().subscribe("pause", [this] { this->pause(); });

    current_track = Game::get_sound_manager().post_event(L"Track_2_event");

    // init tetris field (model, controller, view)
    field = new Field();
    field_controller = new FieldController(*field);
    field_view = new FieldView(*field);

    field_controller->new_next(Tetramino());
    field_controller->new_active(Tetramino());

    Game::get_input_manager().subscribe("left", [this] { this->field_controller->move_active(-1, 0); });
    Game::get_input_manager().subscribe("right", [this] { this->field_controller->move_active(1, 0); });


    
    field_view->set_back_texture(AssetPath + "\\Textures\\Mesopotamia_grid.png");
    field_view->set_palette(AssetPath + "\\Textures\\Mesopotamia_bricks.png");

    field_view->setPosition({ 580.f, 64.f });

    field_view->prerender_tetramino(field->get_active());

    add_drawable(*field_view, 1);

    return true;
}

bool Gameplay::save()
{
	return false;
}

void Gameplay::unload()
{
    gui->get<tgui::Group>(gameplay_scene)->setVisible(false);
    gui->get<tgui::Group>("pause")->setVisible(false);

}

void Gameplay::update(sf::Time elapsed_time)
{
}
