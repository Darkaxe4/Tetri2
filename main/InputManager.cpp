#include "Includes.hpp"


InputManager::InputManager():
	event_handlers(),
	keybinds()
{
}

void InputManager::bind_key(sf::Keyboard::Key key, std::string_view action)
{
	keybinds[key] = action.data();
}

void InputManager::subscribe(std::string_view action, std::function<void()> handler)
{
	event_handlers[action.data()] = handler;
}

void InputManager::process_input(sf::Event event)
{
	if (auto search = keybinds.find(event.getIf<sf::Event::KeyPressed>()->code); search != keybinds.end())
	{
		if (auto event_handler = event_handlers.find(search->second); event_handler != event_handlers.end())
			event_handler->second();
	}
}

void InputManager::call_manually(std::string_view action)
{
	if (auto event_handler = event_handlers.find(action.data()); event_handler != event_handlers.end())
		event_handler->second();
}

