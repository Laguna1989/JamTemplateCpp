﻿#ifndef INCLUDE_MOCKGAME_HPP
#define INCLUDE_MOCKGAME_HPP

#include "game_interface.hpp"
#include <gmock/gmock.h>

class MockGame : public jt::GameInterface {
public:
    MOCK_METHOD(std::shared_ptr<jt::InputManagerInterface>, input, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::MusicPlayerInterface>, getMusicPlayer, (), (override));

    MOCK_METHOD(std::shared_ptr<jt::CamInterface>, getCamera, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::CamInterface>, getCamera, (), (const, override));

    MOCK_METHOD(std::shared_ptr<jt::StateManagerInterface>, stateManager, (), (override));

    MOCK_METHOD(void, setRenderTarget, (std::shared_ptr<jt::renderTarget>), (override));
    MOCK_METHOD(std::shared_ptr<jt::renderTarget>, getRenderTarget, (), (const, override));

    MOCK_METHOD(void, run, (), (override));
    MOCK_METHOD(void, startGame, (jt::GameLoopInterface::GameLoopFunctionPtr), (override));

    MOCK_METHOD(void, setupRenderTarget, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::RenderWindowInterface>, getRenderWindow, (), (const, override));

protected:
    MOCK_METHOD(std::weak_ptr<jt::GameInterface>, getPtr, (), (override));
};

#endif