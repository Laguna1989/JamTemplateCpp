﻿#ifndef JAMTEMPLATE_UNITTEST_MOCKWINDOW_HPP
#define JAMTEMPLATE_UNITTEST_MOCKWINDOW_HPP

#include <graphics/render_window_interface.hpp>
#include <sprite.hpp>
#include <gmock/gmock.h>

class MockWindow : public ::jt::RenderWindowInterface {
public:
    MOCK_METHOD(bool, isOpen, (), (const, override));
    MOCK_METHOD(void, checkForClose, (), (override));
    MOCK_METHOD(jt::Vector2f, getSize, (), (const, override));
    MOCK_METHOD(void, draw, (std::unique_ptr<jt::Sprite>&), (override));
    MOCK_METHOD(void, display, (), (override));
    MOCK_METHOD(jt::Vector2f, getMousePosition, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::RenderTargetLayer>, createRenderTarget, (), (override));
    MOCK_METHOD(void, setMouseCursorVisible, (bool), (override));
    MOCK_METHOD(bool, getMouseCursorVisible, (), (const, override));
    MOCK_METHOD(void, updateGui, (float), (override));
    MOCK_METHOD(void, startRenderGui, (), (override));
    MOCK_METHOD(bool, shouldProcessKeyboard, (), (override));
    MOCK_METHOD(bool, shouldProcessMouse, (), (override));
};

#endif
