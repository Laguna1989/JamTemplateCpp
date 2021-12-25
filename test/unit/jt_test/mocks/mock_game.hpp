#ifndef INCLUDE_MOCKGAME_HPP
#define INCLUDE_MOCKGAME_HPP

#include "game_interface.hpp"
#include "logging/logger_null.hpp"
#include "music_player_interface.hpp"
#include "render_window_null.hpp"
#include <gmock/gmock.h>

class MockGame : public jt::GameInterface {
public:
    MockGame()
    {
        ON_CALL(*this, getRenderWindow).WillByDefault(::testing::ReturnRef(window));
        ON_CALL(*this, getLogger).WillByDefault(::testing::ReturnRef(logger));
    }
    MOCK_METHOD(jt::InputManagerInterface&, input, (), (override));
    MOCK_METHOD(jt::MusicPlayerInterface&, getMusicPlayer, (), (override));

    MOCK_METHOD(std::shared_ptr<jt::CamInterface>, getCamera, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::CamInterface>, getCamera, (), (const, override));

    MOCK_METHOD(std::shared_ptr<jt::StateManagerInterface>, getStateManager, (), (override));

    MOCK_METHOD(std::shared_ptr<jt::renderTarget>, getRenderTarget, (), (const, override));

    MOCK_METHOD(void, runOneFrame, (), (override));
    MOCK_METHOD(void, startGame, (jt::GameInterface::GameLoopFunctionPtr), (override));

    MOCK_METHOD(jt::RenderWindowInterface&, getRenderWindow, (), (const, override));
    MOCK_METHOD(std::shared_ptr<jt::TextureManagerInterface>, getTextureManager, (), (override));
    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(jt::LoggerInterface&, getLogger, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::ActionCommandManagerInterface>, getActionCommandManager, (),
        (override));

protected:
    MOCK_METHOD(std::weak_ptr<jt::GameInterface>, getPtr, (), (override));
    jt::null_objects::LoggerNull logger;
    jt::null_objects::RenderWindowNull window { 100, 200, "abc" };
};

#endif
