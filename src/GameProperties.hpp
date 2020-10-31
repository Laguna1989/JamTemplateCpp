#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

#include <SFML/Graphics/Color.hpp>
#include <string>

class GP {
public:
    GP() = delete;

    static sf::Color PaletteBackground() { return sf::Color { 14, 16, 20 }; };
    static sf::Color PaletteFontFront() { return sf::Color { 248, 249, 254 }; };
    static sf::Color PaletteFontShadow(sf::Uint8 a = 255) { return sf::Color { 26, 29, 36, a }; };
    static sf::Color PaletteSelector() { return sf::Color { 221, 228, 236 }; };
    static sf::Color PaletteHighlight() { return sf::Color { 163, 183, 205 }; };

    static sf::Color PaletteColor1() { return sf::Color { 38, 70, 83 }; };
    static sf::Color PaletteColor2() { return sf::Color { 42, 157, 143 }; };
    static sf::Color PaletteColor3() { return sf::Color { 233, 196, 106 }; };
    static sf::Color PaletteColor4() { return sf::Color { 244, 162, 97 }; };
    static sf::Color PaletteColor5() { return sf::Color { 231, 111, 81 }; };

    static sf::Color PaletteFlashGreen() { return sf::Color { 51, 143, 63 }; };
    static sf::Color PaletteFlashRed() { return sf::Color { 143, 33, 33 }; };

    static std::string GameName() { return "MyAwesomeGame"; };
};

#endif
