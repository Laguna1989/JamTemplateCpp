#ifndef MOCKINPUT_HPP
#define MOCKINPUT_HPP

#include <input/input_manager_interface.hpp>
#include <input/keyboard/keyboard_input_null.hpp>
#include <input/mouse/mouse_input_null.hpp>
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
    MockInput()
    {
        m_keyboard = std::make_shared<jt::KeyboardInputNull>();
        m_mouse = std::make_shared<jt::MouseInputNull>();
        ON_CALL(*this, mouse())
            .WillByDefault(::testing::Invoke(
                [this]() -> std::shared_ptr<jt::MouseInterface> { return m_mouse; }));
        ON_CALL(*this, keyboard())
            .WillByDefault(::testing::Invoke(
                [this]() -> std::shared_ptr<jt::KeyboardInterface> { return m_keyboard; }));
    }

    MOCK_METHOD(std::shared_ptr<jt::MouseInterface>, mouse, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::KeyboardInterface>, keyboard, (), (override));

    MOCK_METHOD(void, update, (bool, bool, jt::MousePosition const&, float), (override));
    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::GamepadInterface>, gamepad, (int), (override));
    MOCK_METHOD(size_t, getNumberOfGamepads, (), (const, override));

private:
    std::shared_ptr<jt::KeyboardInputNull> m_keyboard { nullptr };
    std::shared_ptr<jt::MouseInputNull> m_mouse { nullptr };
};

#endif
