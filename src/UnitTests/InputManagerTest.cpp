
#include "../JamTemplate/InputManager.hpp"
#include "gtest/gtest.h"

using JamTemplate::InputManager;

TEST(InputManagerTest, InitialKeyValuesAfterReset)
{
    InputManager::reset();
    auto const allKeys = JamTemplate::InputHelper::getAllKeys();
    for (auto const k : allKeys) {
        EXPECT_EQ(InputManager::justPressed(k), false);
        EXPECT_EQ(InputManager::justReleased(k), false);
        EXPECT_EQ(InputManager::pressed(k), false);
        EXPECT_EQ(InputManager::released(k), false);
    }
}

TEST(InputManagerTest, InitialButtonValuesAfterReset)
{
    InputManager::reset();
    auto const allButtons = JamTemplate::InputHelper::getAllMouseButtons();
    for (auto const b : allButtons) {
        EXPECT_EQ(InputManager::justPressed(b), false);
        EXPECT_EQ(InputManager::justReleased(b), false);
        EXPECT_EQ(InputManager::pressed(b), false);
        EXPECT_EQ(InputManager::released(b), false);
    }
}

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
    EXPECT_EQ(InputManager::getMousePositionScreen().x, 0.0f);
    EXPECT_EQ(InputManager::getMousePositionScreen().y, 0.0f);

    EXPECT_EQ(InputManager::getMousePositionWorld().x, 0.0f);
    EXPECT_EQ(InputManager::getMousePositionWorld().y, 0.0f);

    // second update will actually set the values.
    InputManager::update(mx, my, mxs, mys, 1.0f);
    EXPECT_EQ(InputManager::getMousePositionScreen().x, mxs);
    EXPECT_EQ(InputManager::getMousePositionScreen().y, mys);

    EXPECT_EQ(InputManager::getMousePositionWorld().x, mx);
    EXPECT_EQ(InputManager::getMousePositionWorld().y, my);
}
