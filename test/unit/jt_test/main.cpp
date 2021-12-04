#include "texture_manager.hpp"
#include <gtest/gtest.h>

#if !USE_SFML
#include "sdl_setup.hpp"
SDLSetup setup;
#endif

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();
    // TODO DI TextureManager to avoid this call
    jt::TextureManager::reset();
    return result;
}
