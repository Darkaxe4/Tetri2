#include "includes.hpp"

InterfaceElement::InterfaceElement(sf::Texture* t):
	texture(t),
	sprite(*t),
	alignment(Alignment::none),
	parent(nullptr)
{

}

void InterfaceElement::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (parent)
		states.transform *= parent->getTransform();
	states.transform *= getTransform();
	target.draw(sprite, states);
}

InterfacePanel::InterfacePanel(sf::Texture* t):
	InterfaceElement(t)
{
}

void InterfacePanel::init()
{
}

void InterfacePanel::update(sf::Time elapsed_time)
{
}
