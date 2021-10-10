#include <gtest/gtest.h>

#if USE_SDL
#include "sdl_setup.hpp"
SDLSetup setup;
#endif

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
