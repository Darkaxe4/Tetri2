#pragma once

class MainMenu;

class BaseMainMenuState
{
public:
	virtual void on_enter() = 0;
	virtual void process_back(MainMenu* ptr) = 0;
	virtual void on_exit() = 0;
};

class MainMenu : public BaseScene
{
private:
	std::unique_ptr<sf::Texture> background;
	std::unique_ptr<sf::Texture> gui_atlas;

	void bind_input() override;

	BaseMainMenuState* state;
	inline void back_handler() { state->process_back(this); }
public:
	MainMenu();

	void set_state(BaseMainMenuState* new_state);

	// Inherited via BaseScene
	bool load() override;

	bool save() override;

	void unload() override;

	void update(sf::Time elapsed_time) override;

};



class MainState :
	public BaseMainMenuState
{
private:

public:
	// Inherited via BaseMainMenuState
	void on_enter() override;
	void process_back(MainMenu* ptr) override;
	void on_exit() override;
};

class SettingsState :
	public BaseMainMenuState
{
private:
	bool save_settings = false;
public:
	void on_enter() override;
	void process_back(MainMenu* ptr) override;
	void on_exit() override;
};