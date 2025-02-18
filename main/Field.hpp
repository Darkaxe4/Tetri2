#pragma once

enum boundCheckResult
{
    SUCCESS = 0,
    BOUND = 1,
    FILLEDCELL = 2,
};

class Field : public I_JSONSerializable
{
private:
    std::vector<std::vector<int>> cells{ {} };

    sf::Vector2i backup[4];
    sf::Vector2<size_t> size{ size_t(19), size_t{29} };

    int currentScore{ 0 };
public:
    Field();

    boundCheckResult check_bounds(Tetramino* active, bool isVerticalTransform);

    inline auto const& get_size() { return size; }

    const std::vector<std::vector<int>>& get_cells();

    int solidify(Tetramino* tetramino);
    
    void swapRows(int lowerRowIndex);
    int clear_full_rows();

    void clear();

    // Inherited via I_JSONSerializable
    virtual json& to_json() override;
    virtual void from_json(json& json) override;
};

class FieldController
{
private:
    Field* field;
    Tetramino* active;
    Tetramino* next;
public:
    FieldController(Field* field);

    void move_active(int dx, int dy);
    void rotate_active();

    inline auto const& get_active() { return *active; };
    inline auto const& get_next() { return *next; };
};


class FieldView: public sf::Drawable
{
private:
    Field* field;

    sf::Texture backgroundTexture;
    sf::Texture brickPaletteTexture;
    sf::Texture fieldTexture;

    sf::RenderTexture fieldPrerender;
    sf::RenderTexture tetraminoPrerender;

    sf::Vector2f margin{ 16.f, 16.f };
    sf::Vector2i brickSize{ 32, 32 };
    sf::Vector2i size{ 19, 29 };
    sf::Vector2f fieldPosition{ 256.f, 64.f };

    sf::Sprite brick;
    sf::Sprite fieldSprite;

    Tetramino* active;
    Tetramino* next;

public:
    void prerender_field();
    void prerender_tetramino(unsigned int type, Color color);
    FieldView(Field& field);

    // Inherited via Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};