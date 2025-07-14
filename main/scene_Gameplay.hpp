#pragma once

class Gameplay;

class GameplaySceneBaseState
{
protected:
    Gameplay* ptr;
public:
    GameplaySceneBaseState(Gameplay* ptr) : ptr(ptr) {}
    virtual void on_enter() = 0;
    virtual void process_back() = 0;
    virtual void process_update(sf::Time elapsed_time) = 0;
    virtual void on_exit() = 0;
};

class Gameplay :
    public BaseScene
{
private:

    std::unique_ptr<sf::Texture> background;

    AkPlayingID current_track;

    GameplaySceneBaseState* state;

    virtual void bind_input() override;
public:
    Gameplay();
    // Inherited via BaseScene
    bool load() override;
    bool save() override;
    void unload() override;
    void update(sf::Time elapsed_time) override;

    void set_state(GameplaySceneBaseState* new_state);
    inline const auto& get_current_track() { return current_track; }
};


class StateRunning :
    public GameplaySceneBaseState
{
private:

public:
    StateRunning(Gameplay* ptr) : GameplaySceneBaseState(ptr) {}
    // Inherited via GameplaySceneBaseState
    void on_enter() override;

    void process_back() override;

    void process_update(sf::Time elapsed_time) override;

    void on_exit() override;

};

class StatePaused :
    public GameplaySceneBaseState
{
private:
    tgui::Group::Ptr pause_group;
public:
    StatePaused(Gameplay* ptr) : GameplaySceneBaseState(ptr) {}

    // Inherited via GameplaySceneBaseState
    void on_enter() override;

    void process_back() override;

    void process_update(sf::Time elapsed_time) override;

    void on_exit() override;

};