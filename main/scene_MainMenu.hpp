#pragma once

class MainMenu : public BaseScene
{
private:
	std::unique_ptr<sf::Texture> background;
	std::unique_ptr<sf::Texture> gui_atlas;
public:
	MainMenu();
	// Inherited via BaseScene
	bool load() override;

	bool save() override;

	void unload() override;

	void update(sf::Time elapsed_time) override;

};