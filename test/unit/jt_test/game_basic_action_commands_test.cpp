#include "action_commands/basic_action_commands.hpp"
#include "game_test.hpp"
#include "mocks/mock_game.hpp"
#include <gtest/gtest.h>

using BasicActionCommandsWithGame = GameTest;

TEST_F(BasicActionCommandsWithGame, CamReset)
{
    addBasicActionCommands(g);
    EXPECT_CALL(camera, reset());
    g->getActionCommandManager().executeCommand("cam.reset");
}

TEST_F(BasicActionCommandsWithGame, CamShake)
{
    addBasicActionCommands(g);

    EXPECT_CALL(camera, shake(::testing::_, ::testing::_, ::testing::_));
    g->getActionCommandManager().executeCommand("cam.shake 1 2");
}

TEST_F(BasicActionCommandsWithGame, CamMove)
{
    addBasicActionCommands(g);

    EXPECT_CALL(camera, move(jt::Vector2f { 100.0f, 200.0f }));
    g->getActionCommandManager().executeCommand("cam.move 100 200");
}

TEST_F(BasicActionCommandsWithGame, CamPos)
{
    addBasicActionCommands(g);

    EXPECT_CALL(camera, setCamOffset(jt::Vector2f { 20.0f, 400.0f }));
    g->getActionCommandManager().executeCommand("cam.pos 20 400");
}

TEST_F(BasicActionCommandsWithGame, CamZoom)
{
    addBasicActionCommands(g);

    EXPECT_CALL(camera, setZoom(2.5f));
    g->getActionCommandManager().executeCommand("cam.zoom 2.5");
}

// TODO Think about a meaningful verification
TEST_F(BasicActionCommandsWithGame, Help)
{
    addBasicActionCommands(g);
    ASSERT_NO_THROW(g->getActionCommandManager().executeCommand("help"));
}

TEST_F(BasicActionCommandsWithGame, Clear)
{
    addBasicActionCommands(g);
    EXPECT_CALL(logger, clear);
    ASSERT_NO_THROW(g->getActionCommandManager().executeCommand("clear"));
}

// TODO Think about a meaningful verification
TEST_F(BasicActionCommandsWithGame, TextureManagerInfo)
{
    addBasicActionCommands(g);
    ASSERT_NO_THROW(g->getActionCommandManager().executeCommand("textureManagerInfo"));
}
