#ifndef INCLUDE_MOCKGAME_HPP
#define INCLUDE_MOCKGAME_HPP

#include <cache/cache_null.hpp>
#include <game_interface.hpp>
#include <graphics/render_window_null.hpp>
#include <log/logger_null.hpp>
#include <mocks/mock_gfx.hpp>
#include <gmock/gmock.h>

class MockGame : public jt::GameInterface {
public:
    MockGame()
    {
        ON_CALL(*this, logger).WillByDefault(::testing::ReturnRef(m_logger));
        ON_CALL(*this, gfx).WillByDefault(::testing::ReturnRef(m_gfx));
        ON_CALL(*this, cache).WillByDefault(::testing::ReturnRef(m_cache));
    }

    MOCK_METHOD(jt::GfxInterface&, gfx, (), (const, override));

    MOCK_METHOD(jt::InputGetInterface&, input, (), (override));
    MOCK_METHOD(jt::AudioInterface&, audio, (), (override));

    MOCK_METHOD(jt::StateManagerInterface&, stateManager, (), (override));

    MOCK_METHOD(jt::LoggerInterface&, logger, (), (override));
    MOCK_METHOD(jt::ActionCommandManagerInterface&, actionCommandManager, (), (override));

    MOCK_METHOD(jt::CacheInterface&, cache, (), (override));

    MOCK_METHOD(void, reset, (), (override));

    ::testing::NiceMock<MockGfx> m_gfx;

protected:
    MOCK_METHOD(std::weak_ptr<jt::GameInterface>, getPtr, (), (override));
    jt::null_objects::LoggerNull m_logger;
    jt::CacheNull m_cache;
};

#endif
