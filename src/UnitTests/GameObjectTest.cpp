#include "GameObject.hpp"
#include "Game.hpp"
#include "gtest/gtest.h"

using jt::Game;
using jt::GameObject;

TEST(GameObjectTest, CreateWithOutGameInstanceSet)
{
    GameObject go {};
    EXPECT_THROW(go.create(), std::logic_error);
}

TEST(GameObjectTest, GameObjectCallsDoNotThrow)
{
    auto const g = std::make_shared<Game>(100, 100, 1.0f, "test");
    GameObject go {};
    go.setGameInstance(g);

    EXPECT_NO_THROW(go.create());
    EXPECT_NO_THROW(go.update(1.2f));
    EXPECT_NO_THROW(go.draw());

    EXPECT_TRUE(go.isAlive());
    EXPECT_NO_THROW(go.kill());
    EXPECT_FALSE(go.isAlive());
}
