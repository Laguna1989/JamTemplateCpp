#include "game_properties.hpp"
jt::Palette GP::getPalette()
{
    return jt::Palette { { jt::Color { 5, 64, 71 }, jt::Color { 32, 142, 68 },
        jt::Color { 133, 225, 66 }, jt::Color { 239, 255, 124 }, jt::Color { 251, 114, 48 },
        jt::Color { 184, 39, 45 }, jt::Color { 64, 23, 58 }, jt::Color { 157, 64, 43 } } };
}

int GP::PhysicVelocityIterations() { return 20; }

int GP::PhysicPositionIterations() { return 20; }
