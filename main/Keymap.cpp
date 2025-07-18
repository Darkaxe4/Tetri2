#include "keymap.hpp"

namespace KeyMap {

    const std::unordered_map<sf::Keyboard::Key, std::string> keyToString = {
        {sf::Keyboard::Key::A, "A"},
        {sf::Keyboard::Key::B, "B"},
        {sf::Keyboard::Key::C, "C"},
        {sf::Keyboard::Key::D, "D"},
        {sf::Keyboard::Key::E, "E"},
        {sf::Keyboard::Key::F, "F"},
        {sf::Keyboard::Key::G, "G"},
        {sf::Keyboard::Key::H, "H"},
        {sf::Keyboard::Key::I, "I"},
        {sf::Keyboard::Key::J, "J"},
        {sf::Keyboard::Key::K, "K"},
        {sf::Keyboard::Key::L, "L"},
        {sf::Keyboard::Key::M, "M"},
        {sf::Keyboard::Key::N, "N"},
        {sf::Keyboard::Key::O, "O"},
        {sf::Keyboard::Key::P, "P"},
        {sf::Keyboard::Key::Q, "Q"},
        {sf::Keyboard::Key::R, "R"},
        {sf::Keyboard::Key::S, "S"},
        {sf::Keyboard::Key::T, "T"},
        {sf::Keyboard::Key::U, "U"},
        {sf::Keyboard::Key::V, "V"},
        {sf::Keyboard::Key::W, "W"},
        {sf::Keyboard::Key::X, "X"},
        {sf::Keyboard::Key::Y, "Y"},
        {sf::Keyboard::Key::Z, "Z"},
        {sf::Keyboard::Key::Num0, "Num0"},
        {sf::Keyboard::Key::Num1, "Num1"},
        {sf::Keyboard::Key::Num2, "Num2"},
        {sf::Keyboard::Key::Num3, "Num3"},
        {sf::Keyboard::Key::Num4, "Num4"},
        {sf::Keyboard::Key::Num5, "Num5"},
        {sf::Keyboard::Key::Num6, "Num6"},
        {sf::Keyboard::Key::Num7, "Num7"},
        {sf::Keyboard::Key::Num8, "Num8"},
        {sf::Keyboard::Key::Num9, "Num9"},
        {sf::Keyboard::Key::Escape, "Escape"},
        {sf::Keyboard::Key::LControl, "LControl"},
        {sf::Keyboard::Key::LShift, "LShift"},
        {sf::Keyboard::Key::LAlt, "LAlt"},
        {sf::Keyboard::Key::LSystem, "LSystem"},
        {sf::Keyboard::Key::RControl, "RControl"},
        {sf::Keyboard::Key::RShift, "RShift"},
        {sf::Keyboard::Key::RAlt, "RAlt"},
        {sf::Keyboard::Key::RSystem, "RSystem"},
        {sf::Keyboard::Key::Menu, "Menu"},
        {sf::Keyboard::Key::LBracket, "LBracket"},
        {sf::Keyboard::Key::RBracket, "RBracket"},
        {sf::Keyboard::Key::Semicolon, "Semicolon"},
        {sf::Keyboard::Key::Comma, "Comma"},
        {sf::Keyboard::Key::Period, "Period"},
        {sf::Keyboard::Key::Apostrophe, "Apostrophe"},
        {sf::Keyboard::Key::Slash, "Slash"},
        {sf::Keyboard::Key::Backslash, "Backslash"},
        {sf::Keyboard::Key::Grave, "Tilde"},
        {sf::Keyboard::Key::Equal, "Equal"},
        {sf::Keyboard::Key::Space, "Space"},
        {sf::Keyboard::Key::Enter, "Return"},
        {sf::Keyboard::Key::Backspace, "Backspace"},
        {sf::Keyboard::Key::Tab, "Tab"},
        {sf::Keyboard::Key::PageUp, "PageUp"},
        {sf::Keyboard::Key::PageDown, "PageDown"},
        {sf::Keyboard::Key::End, "End"},
        {sf::Keyboard::Key::Home, "Home"},
        {sf::Keyboard::Key::Insert, "Insert"},
        {sf::Keyboard::Key::Delete, "Delete"},
        {sf::Keyboard::Key::Add, "Add"},
        {sf::Keyboard::Key::Subtract, "Subtract"},
        {sf::Keyboard::Key::Multiply, "Multiply"},
        {sf::Keyboard::Key::Divide, "Divide"},
        {sf::Keyboard::Key::Left, "Left"},
        {sf::Keyboard::Key::Right, "Right"},
        {sf::Keyboard::Key::Up, "Up"},
        {sf::Keyboard::Key::Down, "Down"},
        {sf::Keyboard::Key::Numpad0, "Numpad0"},
        {sf::Keyboard::Key::Numpad1, "Numpad1"},
        {sf::Keyboard::Key::Numpad2, "Numpad2"},
        {sf::Keyboard::Key::Numpad3, "Numpad3"},
        {sf::Keyboard::Key::Numpad4, "Numpad4"},
        {sf::Keyboard::Key::Numpad5, "Numpad5"},
        {sf::Keyboard::Key::Numpad6, "Numpad6"},
        {sf::Keyboard::Key::Numpad7, "Numpad7"},
        {sf::Keyboard::Key::Numpad8, "Numpad8"},
        {sf::Keyboard::Key::Numpad9, "Numpad9"},
        {sf::Keyboard::Key::F1, "F1"},
        {sf::Keyboard::Key::F2, "F2"},
        {sf::Keyboard::Key::F3, "F3"},
        {sf::Keyboard::Key::F4, "F4"},
        {sf::Keyboard::Key::F5, "F5"},
        {sf::Keyboard::Key::F6, "F6"},
        {sf::Keyboard::Key::F7, "F7"},
        {sf::Keyboard::Key::F8, "F8"},
        {sf::Keyboard::Key::F9, "F9"},
        {sf::Keyboard::Key::F10, "F10"},
        {sf::Keyboard::Key::F11, "F11"},
        {sf::Keyboard::Key::F12, "F12"},
        {sf::Keyboard::Key::Pause, "Pause"}
    };

    const std::unordered_map<std::string, sf::Keyboard::Key> stringToKey = [] {
        std::unordered_map<std::string, sf::Keyboard::Key> map;
        for (const auto& [key, name] : keyToString)
            map[name] = key;
        return map;
        }();

    sf::Keyboard::Key getKeyFromString(const std::string& str) {
        auto it = stringToKey.find(str);
        return (it != stringToKey.end()) ? it->second : sf::Keyboard::Key::Unknown;
    }

    std::string getStringFromKey(sf::Keyboard::Key key) {
        auto it = keyToString.find(key);
        return (it != keyToString.end()) ? it->second : "Unknown";
    }

} // namespace KeyMap
