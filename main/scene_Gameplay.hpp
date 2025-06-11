#pragma once
class Gameplay :
    public BaseScene
{
private:
    std::unique_ptr<sf::Texture> background;

    // tetris field
    Field *field;
    FieldController *field_controller;
    FieldView* field_view;
    void pause();

    AkPlayingID current_track;

    float tetramino_fall_delay;
public:
    Gameplay();
    // Inherited via BaseScene
    bool load() override;
    bool save() override;
    void unload() override;
    void update(sf::Time elapsed_time) override;
};

