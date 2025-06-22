#pragma once

class InputManager
{
private:
	std::map<std::string, std::function<void()>> event_handlers;
	std::map<sf::Keyboard::Key, std::string> keybinds;
public:
	InputManager();

	void bind_key(sf::Keyboard::Key key, std::string_view action);
	void subscribe(std::string_view action, std::function<void()> handler);
	void process_input(sf::Event event);
	void call_manually(std::string_view action);
};

