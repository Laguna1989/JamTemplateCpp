#include "input/input_manager.hpp"
#include "mocks/mock_input.hpp"
#include <gtest/gtest.h>

TEST(InputManagerTest, ReturnsNullptrIfInstantiatedWithNullptr)
{
    jt::InputManager im { nullptr, nullptr };
    EXPECT_EQ(im.keyboard(), nullptr);
    EXPECT_EQ(im.mouse(), nullptr);
}

TEST(InputManagerTest, ResetWithNullptrs)
{
    jt::InputManager im { nullptr, nullptr };
    EXPECT_NO_THROW(im.reset());
}

TEST(InputManagerTest, ReturnsCorrectPointers)
{
    auto keyboard = std::make_shared<MockKeyboardInput>();
    auto mouse = std::make_shared<MockMouseInput>();
    jt::InputManager im { mouse, keyboard };

    EXPECT_EQ(im.keyboard(), keyboard);
    EXPECT_EQ(im.mouse(), mouse);
}

TEST(InputManagerTest, ResetWithMocks)
{
    auto keyboard = std::make_shared<MockKeyboardInput>();
    auto mouse = std::make_shared<MockMouseInput>();
    jt::InputManager im { mouse, keyboard };

    EXPECT_CALL(*mouse, reset);
    EXPECT_CALL(*keyboard, reset);
    im.reset();
}

TEST(InputManagerTest, UpdateWithMocks)
{
    auto keyboard = std::make_shared<MockKeyboardInput>();
    auto mouse = std::make_shared<MockMouseInput>();
    jt::InputManager im { mouse, keyboard };

    jt::MousePosition const mp { 1.0f, 2.0f, 3.0f, 4.0f };
    EXPECT_CALL(*keyboard, updateKeys());
    EXPECT_CALL(*mouse, updateMousePosition(::testing::_));
    EXPECT_CALL(*mouse, updateButtons());
    im.update(mp, 0);
}
