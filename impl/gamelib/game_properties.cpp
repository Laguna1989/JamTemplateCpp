#include "game_properties.hpp"

jt::Palette GP::getPalette()
{
    return jt::Palette::parseGPL("GIMP Palette\n"
                                 "#Palette Name: crayon paint\n"
                                 "#Description: \n"
                                 "#Colors: 8\n"
                                 "118\t161\t241\t76a1f1\n"
                                 "47\t106\t93\t2f6a5d\n"
                                 "105\t191\t43\t69bf2b\n"
                                 "251\t247\t182\tfbf7b6\n"
                                 "233\t142\t51\te98e33\n"
                                 "160\t48\t48\ta03030\n"
                                 "21\t18\t18\t151212\n"
                                 "158\t150\t155\t9e969b");
}

int GP::PhysicVelocityIterations() { return 20; }

int GP::PhysicPositionIterations() { return 20; }
jt::Vector2f GP::PlayerSize() { return jt::Vector2f { 16.0f, 16.0f }; }
