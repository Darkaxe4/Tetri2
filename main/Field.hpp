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

    Tetramino active;
    Tetramino next;
    friend class FieldController;
    friend class FieldView;
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
    virtual void from_json(const json& json) override;
    inline auto const& get_active() { return active; };
    inline auto const& get_next() { return next; };
};

class FieldController
{
private:
    Field* field;
    Tetramino* active;
    Tetramino* next;
public:
    FieldController(Field& field);

    void move_active(int dx, int dy);
    void rotate_active();
};


class FieldView: public sf::Drawable, public sf::Transformable
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
    sf::Vector2u size{ 19, 29 };
    sf::Vector2f fieldPosition{ 256.f, 64.f };

    sf::Sprite brick;
    sf::Sprite tetraminoSprite;
    sf::Sprite fieldSprite;
    sf::Sprite backgroundSprite;

    Tetramino* active;
    Tetramino* next;
public:
    void prerender_field();
    const sf::RenderTexture& prerender_tetramino(const Tetramino& tetramino);
    FieldView(Field& field);

    void set_back_texture(std::string_view path);
    void set_palette(std::string_view path);

    void update_active(const sf::Vector2f& offset = {}, float rotation = 0.f);
    void update();

    // Inherited via Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};