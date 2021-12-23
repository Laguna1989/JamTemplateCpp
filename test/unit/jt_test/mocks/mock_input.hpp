#ifndef MOCKINPUT_HPP_GUARD
#define MOCKINPUT_HPP_GUARD

#include "input/input_manager_interface.hpp"
#include <gmock/gmock.h>

class MockMouseInput : public jt::MouseInputInterface {
public:
    MOCK_METHOD(void, updateMousePosition, (jt::MousePosition const&), (override));
    MOCK_METHOD(void, updateButtons, (), (override));
    MOCK_METHOD(jt::Vector2f, getMousePositionWorld, (), (override));
    MOCK_METHOD(jt::Vector2f, getMousePositionScreen, (), (override));
    MOCK_METHOD(bool, pressed, (jt::MouseButtonCode), (override));
    MOCK_METHOD(bool, justReleased, (jt::MouseButtonCode), (override));
    MOCK_METHOD(bool, justPressed, (jt::MouseButtonCode), (override));
    MOCK_METHOD(bool, released, (jt::MouseButtonCode), (override));
    MOCK_METHOD(void, reset, (), (override));
};

class MockKeyboardInput : public jt::KeyboardInputInterface {
public:
    MOCK_METHOD(void, updateKeys, (), (override));
    MOCK_METHOD(bool, pressed, (jt::KeyCode), (override));
    MOCK_METHOD(bool, released, (jt::KeyCode), (override));
    MOCK_METHOD(bool, justPressed, (jt::KeyCode), (override));

    MOCK_METHOD(void, setCommandPressed,
        (std::vector<jt::KeyCode> const&, std::shared_ptr<jt::ControlCommandInterface>),
        (override));
    MOCK_METHOD(void, setCommandReleased,
        (std::vector<jt::KeyCode> const&, std::shared_ptr<jt::ControlCommandInterface>),
        (override));
    MOCK_METHOD(void, setCommandJustPressed,
        (std::vector<jt::KeyCode> const&, std::shared_ptr<jt::ControlCommandInterface>),
        (override));
    MOCK_METHOD(void, setCommandJustReleased,
        (std::vector<jt::KeyCode> const&, std::shared_ptr<jt::ControlCommandInterface>),
        (override));

    MOCK_METHOD(void, updateCommands, (float), (override));
    MOCK_METHOD(bool, justReleased, (jt::KeyCode), (override));
    MOCK_METHOD(void, reset, (), (override));
};

class MockInput : public jt::InputManagerInterface {
public:
    MOCK_METHOD(std::shared_ptr<jt::MouseInputInterface>, mouse, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::KeyboardInputInterface>, keyboard, (), (override));
    MOCK_METHOD(void, update, (const jt::MousePosition&, float), (override));
    MOCK_METHOD(void, reset, (), (override));
};

#endif
