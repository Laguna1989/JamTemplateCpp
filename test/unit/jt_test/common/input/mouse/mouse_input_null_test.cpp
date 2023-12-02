#include <input/mouse/mouse_input_null.hpp>
#include <gtest/gtest.h>

TEST(MouseInputNullTest, UpdateMousePositionDoesNotThrow)
{
    jt::MouseInputNull mouse;
    jt::MousePosition mp { 0.0f, 0.0f, 0.0f, 0.0f };
    ASSERT_NO_THROW(mouse.updateMousePosition(mp));
}

TEST(MouseInputNullTest, UpdateButtonsDoesNotThrow)
{
    jt::MouseInputNull mouse;
    ASSERT_NO_THROW(mouse.updateButtons());
}

TEST(MouseInputNullTest, ResetDoesNotThrow)
{
    jt::MouseInputNull mouse;
    ASSERT_NO_THROW(mouse.reset());
}

TEST(MouseInputNullTest, PositionWorldReturnsDefault)
{
    jt::MouseInputNull mouse;
    jt::Vector2f const expectedPosition { 0.0f, 0.0f };
    ASSERT_EQ(mouse.getMousePositionWorld(), expectedPosition);
}

TEST(MouseInputNullTest, PositionScreenReturnsDefault)
{
    jt::MouseInputNull mouse;
    jt::Vector2f const expectedPosition { 0.0f, 0.0f };
    ASSERT_EQ(mouse.getMousePositionScreen(), expectedPosition);
}

TEST(MouseInputNullTest, PressedReturnsFalse)
{
    jt::MouseInputNull mouse;
    for (auto const& b : jt::getAllMouseButtons()) {
        ASSERT_FALSE(mouse.pressed(b));
    }
}

TEST(MouseInputNullTest, JustPressedReturnsFalse)
{
    jt::MouseInputNull mouse;
    for (auto const& b : jt::getAllMouseButtons()) {
        ASSERT_FALSE(mouse.justPressed(b));
    }
}

TEST(MouseInputNullTest, ReleasedReturnsFalse)
{
    jt::MouseInputNull mouse;
    for (auto const& b : jt::getAllMouseButtons()) {
        ASSERT_FALSE(mouse.released(b));
    }
}

TEST(MouseInputNullTest, JustReleasedReturnsFalse)
{
    jt::MouseInputNull mouse;
    for (auto const& b : jt::getAllMouseButtons()) {
        ASSERT_FALSE(mouse.justReleased(b));
    }
}
