#pragma once

class Interface : public sf::Drawable
{
private:
	std::vector<sf::Drawable> elements;

public:
	Interface();
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};