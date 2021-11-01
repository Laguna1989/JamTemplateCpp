#include <gtest/gtest.h>

#if !USE_SFML
#include "sdl_setup.hpp"
SDLSetup setup;
#endif

#include <stdlib.h>
setenv("DISPLAY", "127.0.0.1:0", true);

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
