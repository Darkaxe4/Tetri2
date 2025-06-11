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
    sf::Vector2<size_t> size{ size_t(11), size_t{14} };

    int currentScore{ 0 };

    Tetramino active;
    Tetramino next;
    friend class FieldController;
    friend class FieldView;
public:
    Field();

    void clear();
    inline auto const& get_size() { return size; }

    // Inherited via I_JSONSerializable
    virtual json to_json() const override;
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

    boundCheckResult check_bounds(Tetramino* active, bool isVerticalTransform);

    inline void new_next(Tetramino&& tetramino) { *this->next = tetramino; }
    inline void new_active(Tetramino&& tetramino) { *this->active = tetramino; }
    inline void swap_active_next() { active, next = next, active; }

    const std::vector<std::vector<int>>& get_cells();

    int solidify(Tetramino* tetramino);

    void swapRows(int lowerRowIndex);
    int clear_full_rows();
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

    sf::Vector2f margin{ 0.f, 0.f };
    sf::Vector2i brickSize{ 64, 64 };
    sf::Vector2u size{ 11, 14 };
    sf::Vector2f fieldPosition{ 256.f, 64.f };

    sf::Sprite* brick;
    sf::Sprite* tetraminoSprite;
    sf::Sprite* fieldSprite;
    sf::Sprite* backgroundSprite;

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