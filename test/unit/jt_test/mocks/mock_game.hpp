#ifndef INCLUDE_MOCKGAME_HPP
#define INCLUDE_MOCKGAME_HPP

#include "game_interface.hpp"
#include "logging/logger_null.hpp"
#include "mock_gfx.hpp"
#include "render_window_null.hpp"
#include <gmock/gmock.h>

class MockGame : public jt::GameInterface {
public:
    MockGame()
    {
        ON_CALL(*this, getLogger).WillByDefault(::testing::ReturnRef(logger));
        ON_CALL(*this, gfx).WillByDefault(::testing::ReturnRef(m_gfx));
    }

    MOCK_METHOD(jt::GfxInterface&, gfx, (), (const, override));

    MOCK_METHOD(jt::InputManagerInterface&, input, (), (override));
    MOCK_METHOD(jt::AudioInterface&, audio, (), (override));

    MOCK_METHOD(jt::StateManagerInterface&, getStateManager, (), (override));

    MOCK_METHOD(void, runOneFrame, (), (override));
    MOCK_METHOD(void, startGame, (jt::GameInterface::GameLoopFunctionPtr), (override));

    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(jt::LoggerInterface&, getLogger, (), (override));
    MOCK_METHOD(jt::ActionCommandManagerInterface&, getActionCommandManager, (), (override));

    ::testing::NiceMock<MockGfx> m_gfx;

protected:
    MOCK_METHOD(std::weak_ptr<jt::GameInterface>, getPtr, (), (override));
    jt::null_objects::LoggerNull logger;
};

#endif
