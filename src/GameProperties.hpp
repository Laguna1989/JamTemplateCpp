#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

#include "color.hpp"
#include "vector.hpp"
#include <cstdint>
#include <string>

class GP {
public:
    GP() = delete;

    static jt::color PaletteBackground() { return jt::color { 14, 16, 20 }; };
    static jt::color PaletteFontFront() { return jt::color { 248, 249, 254 }; };
    static jt::color PaletteFontShadow(std::uint8_t a = 255)
    {
        return jt::color { 26, 29, 36, a };
    };
    static jt::color PaletteSelector() { return jt::color { 221, 228, 236 }; };
    static jt::color PaletteHighlight() { return jt::color { 163, 183, 205 }; };

    static jt::color PaletteColor1() { return jt::color { 38, 70, 83 }; };
    static jt::color PaletteColor2() { return jt::color { 42, 157, 143 }; };
    static jt::color PaletteColor3() { return jt::color { 233, 196, 106 }; };
    static jt::color PaletteColor4() { return jt::color { 244, 162, 97 }; };
    static jt::color PaletteColor5() { return jt::color { 231, 111, 81 }; };

    static jt::color PaletteFlashGreen() { return jt::color { 51, 143, 63 }; };
    static jt::color PaletteFlashRed() { return jt::color { 143, 33, 33 }; };

    static std::string GameName() { return "MyAwesomeGame"; };
    static jt::vector2 GetWindowSize() { return jt::vector2 { 800, 600 }; }
};

#endif
