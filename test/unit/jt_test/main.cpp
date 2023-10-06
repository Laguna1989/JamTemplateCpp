#include <backend_setup.hpp>
#include <gtest/gtest.h>

#if !USE_SFML
SDLSetup setup;
#endif

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
