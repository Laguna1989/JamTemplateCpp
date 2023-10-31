#include <input/gamepad/gamepad_input.hpp>
#include <input/input_manager.hpp>
#include <mocks/mock_input.hpp>
#include <gtest/gtest.h>

TEST(InputManagerTest, ReturnsKeybaordNullObjIfInstantiatedWithNullptr)
{
    jt::InputManager im { nullptr, nullptr, std::vector<std::shared_ptr<jt::GamepadInterface>> {} };
    ASSERT_NE(im.keyboard(), nullptr);
}

TEST(InputManagerTest, ReturnsMouseNullObjIfInstantiatedWithNullptr)
{
    jt::InputManager im { nullptr, nullptr, std::vector<std::shared_ptr<jt::GamepadInterface>> {} };
    ASSERT_NE(im.mouse(), nullptr);
}

TEST(InputManagerTest, GamepadReturnsNoNullptr)
{
    jt::InputManager im { nullptr, nullptr, std::vector<std::shared_ptr<jt::GamepadInterface>> {} };
    ASSERT_NE(im.gamepad(0), nullptr);
    ASSERT_NE(im.gamepad(1), nullptr);
    ASSERT_NE(im.gamepad(2), nullptr);
    ASSERT_NE(im.gamepad(3), nullptr);
}

TEST(InputManagerTest, ReturnsCorrectPointers)
{
    auto keyboard = std::make_shared<MockKeyboardInput>();
    auto mouse = std::make_shared<MockMouseInput>();
    std::shared_ptr<jt::GamepadInterface> gamepad = std::make_shared<jt::GamepadInput>(0);

    jt::InputManager im { mouse, keyboard, { gamepad } };

    ASSERT_EQ(im.keyboard(), keyboard);
    ASSERT_EQ(im.mouse(), mouse);
    ASSERT_EQ(im.gamepad(0), gamepad);
}

TEST(InputManagerTest, ResetWithNullptrs)
{
    jt::InputManager im { nullptr, nullptr, std::vector<std::shared_ptr<jt::GamepadInterface>> {} };
    ASSERT_NO_THROW(im.reset());
}

TEST(InputManagerTest, ResetWithMocks)
{
    auto keyboard = std::make_shared<MockKeyboardInput>();
    auto mouse = std::make_shared<MockMouseInput>();
    std::shared_ptr<jt::GamepadInterface> gamepad = std::make_shared<jt::GamepadInput>(0);
    jt::InputManager im { mouse, keyboard, { gamepad } };

    EXPECT_CALL(*mouse, reset);
    EXPECT_CALL(*keyboard, reset);
    im.reset();
}

TEST(InputManagerTest, UpdateWithMocks)
{
    auto keyboard = std::make_shared<::testing::NiceMock<MockKeyboardInput>>();
    auto mouse = std::make_shared<::testing::NiceMock<MockMouseInput>>();
    std::shared_ptr<jt::GamepadInterface> gamepad = std::make_shared<jt::GamepadInput>(0);
    jt::InputManager im { mouse, keyboard, { gamepad } };

    jt::MousePosition const mp { 1.0f, 2.0f, 3.0f, 4.0f };
    EXPECT_CALL(*keyboard, updateKeys());
    EXPECT_CALL(*mouse, updateMousePosition(::testing::_));
    EXPECT_CALL(*mouse, updateButtons());
    im.update(false, false, mp, 0);
}

TEST(InputManagerTest, NumberOfGamePadsReturnsZeroByDefault)
{
    jt::InputManager im { nullptr, nullptr, {} };
    ASSERT_EQ(im.getNumberOfGamepads(), 0);
}
