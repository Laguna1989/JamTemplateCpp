#ifndef JAMTEMPLATE_UNITTESTS_GAME_TEST_HPP
#define JAMTEMPLATE_UNITTESTS_GAME_TEST_HPP

#include "action_commands/action_command_manager.hpp"
#include "game.hpp"
#include "mocks/mock_camera.hpp"
#include "mocks/mock_input.hpp"
#include "mocks/mock_state.hpp"
#include "mocks/mock_state_manager.hpp"
#include "mocks/mock_window.hpp"
#include "music_player_null.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class GameTest : public ::testing::Test {
public:
    float const zoom { 1.0f };
    std::shared_ptr<jt::GameBase> g { nullptr };
    MockWindow window;
    MockCamera camera;
    jt::MusicPlayerNull musicPlayer;
    std::shared_ptr<MockState> state { nullptr };
    ::testing::NiceMock<MockInput> input;
    ::testing::NiceMock<MockStateManager> stateManager;
    // TODO use mock or null objects if possible
    jt::Logger logger;
    jt::ActionCommandManager actionCommandManager { logger };

    void SetUp() override
    {
        // getSize has to be called, so that the game knows how big the rendertarget will be.
        ON_CALL(window, getSize()).WillByDefault([]() { return jt::Vector2f { 100.0f, 200.0f }; });

        ON_CALL(camera, getZoom).WillByDefault([this]() { return zoom; });

        state = std::make_shared<MockState>();
        ON_CALL(stateManager, getCurrentState).WillByDefault(::testing::Return(state));

        g = std::make_shared<jt::Game>(
            window, input, musicPlayer, camera, stateManager, logger, actionCommandManager);
        state->setGameInstance(g);
    }
};

#endif // JAMTEMPLATE_UNITTESTS_GAME_TEST_HPP
