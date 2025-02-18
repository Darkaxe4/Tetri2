#pragma once

class IRenderer
{
public:
	virtual void Render(sf::RenderTarget&) = 0;
};