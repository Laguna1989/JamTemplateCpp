#ifndef JAMTEMPLATE_UNITTESTS_GAME_TEST_HPP
#define JAMTEMPLATE_UNITTESTS_GAME_TEST_HPP

#include "game.hpp"
#include "mocks/mock_camera.hpp"
#include "mocks/mock_input.hpp"
#include "mocks/mock_state.hpp"
#include "mocks/mock_state_manager.hpp"
#include "mocks/mock_window.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <music_player_null.hpp>

class GameTest : public ::testing::Test {
public:
    float const zoom { 1.0f };
    std::shared_ptr<jt::Game> g { nullptr };
    std::shared_ptr<MockWindow> window { nullptr };
    std::shared_ptr<MockCamera> camera { nullptr };
    std::shared_ptr<jt::MusicPlayerInterface> music_player { nullptr };
    std::shared_ptr<MockState> state { nullptr };

    void SetUp() override
    {
        window = std::make_shared<::testing::NiceMock<MockWindow>>();
        // getSize has to be called, so that the game knows how big the rendertarget will be.
        ON_CALL(*window, getSize()).WillByDefault([]() { return jt::Vector2 { 100.0f, 200.0f }; });

        auto input = std::make_shared<::testing::NiceMock<MockInput>>();

        music_player = std::make_shared<jt::MusicPlayerNull>();

        camera = std::make_shared<::testing::NiceMock<MockCamera>>();
        ON_CALL(*camera, getZoom).WillByDefault([this]() { return zoom; });

        state = std::make_shared<MockState>();
        auto stateManager = std::make_shared<::testing::NiceMock<MockStateManager>>();
        ON_CALL(*stateManager, getCurrentState).WillByDefault(::testing::Return(state));

        g = std::make_shared<jt::Game>(window, input, music_player, camera, stateManager);
    }
};

#endif // JAMTEMPLATE_UNITTESTS_GAME_TEST_HPP
