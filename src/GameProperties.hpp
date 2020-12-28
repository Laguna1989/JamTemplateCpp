#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

#include "Color.hpp"
#include "Vector.hpp"
#include <cstdint>
#include <string>

class GP {
public:
    GP() = delete;

    static std::string GameName() { return "MyAwesomeGame"; }
    static std::string AuthorName() { return "TODO"; }
    static std::string JamName() { return "TODO"; }
    static std::string JamDate() { return "TODO"; }

    static jt::Vector2 GetWindowSize() { return jt::Vector2 { 800, 600 }; }
    static float GetZoom() { return 2.0f; }
    static jt::Vector2 GetScreenSize() { return GetWindowSize() * (1.0f / GetZoom()); }

    static jt::Color PaletteBackground() { return GP::PaletteColor1(); }
    static jt::Color PaletteFontFront() { return GP::PaletteColor4(); }
    static jt::Color PaletteFontShadow() { return GP::PaletteColor6(); }

    static jt::Color PaletteColor1() { return jt::Color { 110, 184, 168 }; }
    static jt::Color PaletteColor2() { return jt::Color { 42, 88, 79 }; }
    static jt::Color PaletteColor3() { return jt::Color { 112, 163, 63 }; }
    static jt::Color PaletteColor4() { return jt::Color { 252, 255, 192 }; }
    static jt::Color PaletteColor5() { return jt::Color { 187, 80, 90 }; }
    static jt::Color PaletteColor6() { return jt::Color { 47, 20, 47 }; }
    static jt::Color PaletteColor7() { return jt::Color { 119, 68, 72 }; }
    static jt::Color PaletteColor8() { return jt::Color { 238, 156, 93 }; }

    static int PhysicVelocityIterations() { return 6; }
    static int PhysicPositionIterations() { return 2; }
};

#endif
