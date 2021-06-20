﻿#ifndef MOCKINPUT_HPP_GUARD
#define MOCKINPUT_HPP_GUARD

#include "input_manager_interface.hpp"
#include <gmock/gmock.h>

class MockMouseInput : public jt::MouseInputInterface {
public:
    MOCK_METHOD(void, updateMousePosition, (jt::MousePosition const&), (override));
    MOCK_METHOD(void, updateButtons, (), (override));
    MOCK_METHOD(jt::Vector2, getMousePositionWorld, (), (override));
    MOCK_METHOD(jt::Vector2, getMousePositionScreen, (), (override));
    MOCK_METHOD(bool, pressed, (jt::MouseButtonCode), (override));
    MOCK_METHOD(bool, justReleased, (jt::MouseButtonCode), (override));
    MOCK_METHOD(bool, justPressed, (jt::MouseButtonCode), (override));
    MOCK_METHOD(bool, released, (jt::MouseButtonCode), (override));
    MOCK_METHOD(void, reset, (), (override));
};

class MockKeyboardInput : public jt::KeyboardInputInterface {
public:
    MOCK_METHOD(void, updateKeys, (), (override));
    MOCK_METHOD(bool, pressed, (jt::KeyCode k), (override));
    MOCK_METHOD(bool, released, (jt::KeyCode k), (override));
    MOCK_METHOD(bool, justPressed, (jt::KeyCode k), (override));
    MOCK_METHOD(bool, justReleased, (jt::KeyCode), (override));
    MOCK_METHOD(void, reset, (), (override));
};

#endif
