#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

#include <SFML/Graphics/Color.hpp>
#include <string>

class GP {
public:
    GP() = delete;

    static float CellPositionSpacing() { return 32.0f; }
    static float CellPositionOffsetX() { return 10.0f; }
    static float CellPositionOffsetY() { return 10.0f; }
    static float GameBoardInputTimerMax() { return 0.6f; }
    static float GameBoardInputOffsetMax() { return 300; }
    static unsigned int GameBoardMaxParse() { return 20; }

    static sf::Color PaletteBackground() { return sf::Color { 14, 16, 20 }; };
    static sf::Color PaletteFontFront() { return sf::Color { 248, 249, 254 }; };
    static sf::Color PaletteFontShadow(sf::Uint8 a = 255) { return sf::Color { 26, 29, 36, a }; };
    static sf::Color PaletteSelector() { return sf::Color { 221, 228, 236 }; };
    static sf::Color PaletteHighlight() { return sf::Color { 163, 183, 205 }; };

    static sf::Color PaletteFlashGreen() { return sf::Color { 51, 143, 63 }; };
    static sf::Color PaletteFlashRed() { return sf::Color { 143, 33, 33 }; };

    static std::string GameName() { return "MyAwesomeGame"; };
};

#endif
