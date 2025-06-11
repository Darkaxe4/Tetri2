#pragma once


enum class Alignment {
	top,
	bottom,
	left,
	right,
	top_left,
	top_right,
	bottom_left,
	bottom_right,
	center,
	none,
};

class InterfaceElement : public sf::Drawable, public sf::Transformable
{
protected:
	InterfaceElement* parent;
	sf::Vector2i size;
	sf::FloatRect padding{ {0, 0}, {0, 0} };
	sf::Texture* texture;
	sf::Sprite sprite;
	Alignment alignment;
public:
	InterfaceElement(sf::Texture* t);

	virtual void init() = 0;
	virtual void update(sf::Time elapsed_time) = 0;

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// setters
	inline void set_padding(sf::FloatRect& rect) { padding = rect; }
	inline void set_texture(sf::Texture* t) { texture = t; }
	inline void set_alignment(Alignment a) { alignment = a; }
};

class InterfacePanel :
	public InterfaceElement
{
private:

public:
	InterfacePanel(sf::Texture* t);

	// Inherited via InterfaceElement
	void init() override;

	void update(sf::Time elapsed_time) override;

};
