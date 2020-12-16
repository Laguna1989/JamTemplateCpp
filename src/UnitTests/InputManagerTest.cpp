#include "InputManager.hpp"
#include "gtest/gtest.h"

using jt::InputManager;

TEST(InputManagerTest, UpdateStoresCorrectMousePosition)
{
    float const mx = 10;
    float const my = 20;
    float const mxs = 30;
    float const mys = 40;

    InputManager::reset();

    // first update will not trigger any changes, to have a small deadtime for input
    // after the game initializes or after a Gamestate switch.
    InputManager::update(mx, my, mxs, mys, 1.0f);
    EXPECT_EQ(InputManager::getMousePositionScreen().x(), 0.0f);
    EXPECT_EQ(InputManager::getMousePositionScreen().y(), 0.0f);

    EXPECT_EQ(InputManager::getMousePositionWorld().x(), 0.0f);
    EXPECT_EQ(InputManager::getMousePositionWorld().y(), 0.0f);

    // second update will actually set the values.
    InputManager::update(mx, my, mxs, mys, 1.0f);
    EXPECT_EQ(InputManager::getMousePositionScreen().x(), mxs);
    EXPECT_EQ(InputManager::getMousePositionScreen().y(), mys);

    EXPECT_EQ(InputManager::getMousePositionWorld().x(), mx);
    EXPECT_EQ(InputManager::getMousePositionWorld().y(), my);
}
