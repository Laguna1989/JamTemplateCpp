#ifndef MOCKINPUT_HPP
#define MOCKINPUT_HPP

#include <input/input_manager_interface.hpp>
#include <gmock/gmock.h>

class MockMouseInput : public jt::MouseInterface {
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

class MockKeyboardInput : public jt::KeyboardInterface {
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
    MOCK_METHOD(std::shared_ptr<jt::MouseInterface>, mouse, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::KeyboardInterface>, keyboard, (), (override));
    MOCK_METHOD(void, update, (const jt::MousePosition&, float), (override));
    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::GamepadInterface>, gamepad, (int), (override));
    MOCK_METHOD(size_t, getNumberOfGamepads, (), (const, override));
};

#endif
