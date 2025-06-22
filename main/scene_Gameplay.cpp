#include "Includes.hpp"

void Gameplay::bind_input()
{
    Game::get_input_manager().subscribe("back", [this] { this->state->process_back(); });
    Game::get_input_manager().subscribe("left", [this] { this->field_controller->move_active(-1, 0); });
    Game::get_input_manager().subscribe("right", [this] { this->field_controller->move_active(1, 0); });

}

Gameplay::Gameplay() :
    BaseScene(1),
    background(new sf::Texture()),
    field(nullptr),
    field_controller(nullptr),
    field_view(nullptr),
    current_track(),
    tetramino_fall_delay(0.f),
    state(new StateRunning{this})
{
}

bool Gameplay::load()
{
    if (initialized)
    {
        set_state(new StateRunning{ this });
        bind_input();
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

    continue_btn->onPress([this] {this->state->process_back();});
    back_to_menu_btn->onPress([] {Game::get_scene_manager().load_scene(menu_scene);});
    

    current_track = Game::get_sound_manager().post_event(L"Track_3_event");

    // init tetris field (model, controller, view)
    field = new Field();
    field_controller = new FieldController(*field);
    field_view = new FieldView(*field);

    field_controller->new_next(Tetramino());
    field_controller->new_active(Tetramino());

    bind_input();
    
    field_view->set_back_texture(AssetPath + "\\Textures\\Mesopotamia_grid.png");
    field_view->set_palette(AssetPath + "\\Textures\\Mesopotamia_bricks.png");

    field_view->setPosition({ 580.f, 64.f });

    field_view->prerender_tetramino(field->get_active());

    add_drawable(*field_view, 1);

    set_state(new StateRunning{ this });

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

void Gameplay::set_state(GameplaySceneBaseState* new_state)
{
    if (state)
    {
        state->on_exit();
        delete state;
    }
    state = new_state;
    state->on_enter();
}

void StateRunning::on_enter()
{
    
}

void StateRunning::process_back()
{
    ptr->set_state(new StatePaused{ ptr });
}

void StateRunning::process_update(sf::Time elapsed_time)
{
}

void StateRunning::on_exit()
{
}

void StatePaused::on_enter()
{
    pause_group = Game::get_scene_manager().get_gui()->get<tgui::Group>("pause");
    pause_group->showWithEffect(tgui::ShowEffectType::SlideFromLeft, tgui::Duration{ 200 });
    AK::SoundEngine::ExecuteActionOnPlayingID(AK::SoundEngine::AkActionOnEventType_Pause, ptr->get_current_track());
}

void StatePaused::process_back()
{
    ptr->set_state(new StateRunning{ ptr });
}

void StatePaused::process_update(sf::Time elapsed_time)
{
}

void StatePaused::on_exit()
{
    pause_group->hideWithEffect(tgui::ShowEffectType::SlideToLeft, tgui::Duration{ 200 });
    AK::SoundEngine::ExecuteActionOnPlayingID(AK::SoundEngine::AkActionOnEventType_Resume, ptr->get_current_track());
}
