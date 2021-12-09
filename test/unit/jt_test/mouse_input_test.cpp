#include "input/mouse_input.hpp"
#include "gtest/gtest.h"

TEST(MouseInput, UpdateStoresMousePosition)
{
    jt::MousePosition mp { 10, 20, 30, 40 };

    jt::MouseInput mouseInput { nullptr };
    mouseInput.updateMousePosition(mp);
    EXPECT_EQ(mouseInput.getMousePositionWorld().x, mp.window_x);
    EXPECT_EQ(mouseInput.getMousePositionWorld().y, mp.window_y);

    EXPECT_EQ(mouseInput.getMousePositionScreen().x, mp.screen_x);
    EXPECT_EQ(mouseInput.getMousePositionScreen().y, mp.screen_y);
}

TEST(MouseInput, ResetSetsMousePositionsToZero)
{
    jt::MousePosition mp { 10, 20, 30, 40 };

    jt::MouseInput mouseInput { nullptr };
    mouseInput.updateMousePosition(mp);
    ASSERT_EQ(mouseInput.getMousePositionWorld().x, mp.window_x);
    ASSERT_EQ(mouseInput.getMousePositionWorld().y, mp.window_y);
    ASSERT_EQ(mouseInput.getMousePositionScreen().x, mp.screen_x);
    ASSERT_EQ(mouseInput.getMousePositionScreen().y, mp.screen_y);

    mouseInput.reset();
    EXPECT_EQ(mouseInput.getMousePositionWorld().x, 0);
    EXPECT_EQ(mouseInput.getMousePositionWorld().y, 0);
    EXPECT_EQ(mouseInput.getMousePositionScreen().x, 0);
    EXPECT_EQ(mouseInput.getMousePositionScreen().y, 0);
}

TEST(MouseInput, AllButtonsAlwaysPressed)
{
    jt::MouseInput mouseInput { [](auto /*b*/) { return true; } };
    mouseInput.updateButtons();
    for (auto const b : jt::getAllButtons()) {
        EXPECT_TRUE(mouseInput.pressed(b));
        EXPECT_FALSE(mouseInput.released(b));
    }
}

TEST(MouseInput, AllButtonsAlwaysReleased)
{
    jt::MouseInput mouseInput { [](auto /*b*/) { return false; } };
    mouseInput.updateButtons();
    for (auto const b : jt::getAllButtons()) {
        EXPECT_FALSE(mouseInput.pressed(b));
        EXPECT_TRUE(mouseInput.released(b));
    }
}

TEST(MouseInput, AllButtonsJustPressed)
{
    jt::MouseInput mouseInput { [](auto /*b*/) { return true; } };
    mouseInput.reset();
    mouseInput.updateButtons();
    for (auto const b : jt::getAllButtons()) {
        EXPECT_TRUE(mouseInput.justPressed(b));
        EXPECT_FALSE(mouseInput.justReleased(b));
    }
    mouseInput.updateButtons();
    for (auto const b : jt::getAllButtons()) {
        EXPECT_FALSE(mouseInput.justPressed(b));
        EXPECT_FALSE(mouseInput.justReleased(b));
    }
}

TEST(MouseInput, AllButtonsJustReleased)
{
    int call_count { 0 };
    // return true on first call, false otherwise
    jt::MouseInput mouseInput { [&call_count](auto /*b*/) {
        auto v = (call_count == 0);
        return v;
    } };

    mouseInput.reset();
    mouseInput.updateButtons();
    call_count++;
    for (auto const b : jt::getAllButtons()) {
        ASSERT_TRUE(mouseInput.justPressed(b));
        ASSERT_FALSE(mouseInput.justReleased(b));
    }
    mouseInput.updateButtons();
    for (auto const b : jt::getAllButtons()) {
        EXPECT_FALSE(mouseInput.justPressed(b));
        EXPECT_TRUE(mouseInput.justReleased(b));
    }
}

/*
TEST(GetAll, NoThrow)
{
    EXPECT_NO_THROW(jt::getAllButtons());
    EXPECT_NO_THROW(jt::getAllKeys());
}

TEST(GetAll, NotEmpty)
{
    EXPECT_FALSE(jt::getAllButtons().empty());
    EXPECT_FALSE(jt::getAllKeys().empty());
}
*/
