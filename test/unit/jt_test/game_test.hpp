#ifndef JAMTEMPLATE_UNITTESTS_GAME_TEST_HPP
#define JAMTEMPLATE_UNITTESTS_GAME_TEST_HPP

#include "action_commands/action_command_manager.hpp"
#include "audio/audio_null.hpp"
#include "game.hpp"
#include "mocks/mock_camera.hpp"
#include "mocks/mock_gfx.hpp"
#include "mocks/mock_input.hpp"
#include "mocks/mock_logger.hpp"
#include "mocks/mock_state.hpp"
#include "mocks/mock_state_manager.hpp"
#include "mocks/mock_window.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class GameTest : public ::testing::Test {
public:
    float const zoom { 1.0f };
    std::shared_ptr<jt::GameBase> g { nullptr };
    MockWindow window;
    MockCamera camera;
    jt::TextureManagerImpl textureManager { nullptr };
    MockGfx gfx;
    jt::ActionCommandManager actionCommandManager { logger };
    jt::AudioNull audio;

    std::shared_ptr<MockState> state { nullptr };
    ::testing::NiceMock<MockInput> input;
    ::testing::NiceMock<MockStateManager> stateManager;
    ::testing::NiceMock<MockLogger> logger;

    void SetUp() override
    {
        ON_CALL(gfx, window).WillByDefault(::testing::ReturnRef(window));
        ON_CALL(gfx, camera).WillByDefault(::testing::ReturnRef(camera));
        ON_CALL(gfx, textureManager).WillByDefault(::testing::ReturnRef(textureManager));
        // getSize has to be called, so that the game knows how big the rendertarget will be.
        ON_CALL(window, getSize()).WillByDefault([]() { return jt::Vector2f { 100.0f, 200.0f }; });

        ON_CALL(camera, getZoom).WillByDefault([this]() { return zoom; });

        state = std::make_shared<MockState>();
        ON_CALL(stateManager, getCurrentState).WillByDefault(::testing::Return(state));
        ON_CALL(stateManager, update)
            .WillByDefault(
                ::testing::Invoke([this](auto ptr, auto elapsed) { state->update(elapsed); }));
        g = std::make_shared<jt::Game>(
            gfx, input, audio, stateManager, logger, actionCommandManager);
        state->setGameInstance(g);
    }
};

#endif // JAMTEMPLATE_UNITTESTS_GAME_TEST_HPP
