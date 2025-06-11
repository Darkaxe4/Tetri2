#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <string>

namespace KeyMap {
    extern const std::unordered_map<sf::Keyboard::Key, std::string> keyToString;
    extern const std::unordered_map<std::string, sf::Keyboard::Key> stringToKey;

    // Optional helper
    sf::Keyboard::Key getKeyFromString(const std::string& str);
    std::string getStringFromKey(sf::Keyboard::Key key);
}
