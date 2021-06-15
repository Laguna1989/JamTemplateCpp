#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

#include "color.hpp"
#include "vector.hpp"
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

    static jt::Color PaletteBackground() { return GP::PaletteColor6(); }
    static jt::Color PaletteFontFront() { return GP::PaletteColor4(); }
    static jt::Color PaletteFontShadow() { return GP::PaletteColor7(); }

    static jt::Color PaletteColor1() { return jt::Color { 5, 64, 71 }; }
    static jt::Color PaletteColor2() { return jt::Color { 32, 142, 68 }; }
    static jt::Color PaletteColor3() { return jt::Color { 133, 225, 66 }; }
    static jt::Color PaletteColor4() { return jt::Color { 239, 255, 124 }; }
    static jt::Color PaletteColor5() { return jt::Color { 251, 114, 48 }; }
    static jt::Color PaletteColor6() { return jt::Color { 184, 39, 45 }; }
    static jt::Color PaletteColor7() { return jt::Color { 64, 23, 58 }; }
    static jt::Color PaletteColor8() { return jt::Color { 157, 64, 43 }; }

    static int PhysicVelocityIterations() { return 6; }
    static int PhysicPositionIterations() { return 2; }
};

#endif
