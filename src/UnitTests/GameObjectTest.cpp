#include "GameObject.hpp"
#include "MockGame.hpp"
#include "gtest/gtest.h"

using jt::GameInterface;
using jt::GameObject;

#ifndef ENABLE_WEB
TEST(GameObjectTest, CreateWithOutGameInstanceSet)
{
    GameObject go {};
    EXPECT_THROW(go.create(), std::logic_error);
}

TEST(GameObjectTest, GameObjectCallsDoNotThrow)
{
    auto const g = std::make_shared<MockGame>();
    GameObject go {};
    go.setGameInstance(g);

    EXPECT_NO_THROW(go.create());
    EXPECT_NO_THROW(go.update(1.2f));
    EXPECT_NO_THROW(go.draw());

    EXPECT_TRUE(go.isAlive());
    EXPECT_NO_THROW(go.kill());
    EXPECT_FALSE(go.isAlive());
}

TEST(GameObjectTest, GameObjectAddTwice)
{
    auto const g = std::make_shared<MockGame>();
    GameObject go {};
    go.setGameInstance(g);
    EXPECT_THROW(go.setGameInstance(g), std::logic_error);
}

TEST(GameObjectTest, UpdateLogic)
{
    GameObject go {};
    go.update(0.5f);
    EXPECT_EQ(go.getAge(), 0.5f);

    EXPECT_TRUE(go.isAlive());
    go.kill();
    EXPECT_FALSE(go.isAlive());
}

#endif
