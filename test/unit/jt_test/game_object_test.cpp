#include "game_object.hpp"
#include "mocks/mock_game.hpp"
#include "gtest/gtest.h"

using jt::GameInterface;
using jt::GameObject;

#ifndef JT_ENABLE_WEB
TEST(GameObjectTest, CreateWithOutGameInstanceSet)
{
    GameObject go {};
    ASSERT_THROW(go.create(), std::logic_error);
}

TEST(GameObjectTest, CreateWithGameInstace)
{
    auto const g = std::make_shared<MockGame>();
    GameObject go {};
    go.setGameInstance(g);
    ASSERT_NO_THROW(go.create());
}

TEST(GameObjectTest, IsAliveIsTrueByDEfault)
{
    GameObject go {};
    ASSERT_TRUE(go.isAlive());
}

TEST(GameObjectTest, IsAliveIsFalseAfterKill)
{
    GameObject go {};
    go.kill();
    ASSERT_FALSE(go.isAlive());
}

TEST(GameObjectTest, UpdateDoesNotThrow)
{
    GameObject go {};
    ASSERT_NO_THROW(go.update(1.2f));
}

TEST(GameObjectTest, DrawDoesNotThrow)
{
    GameObject go {};
    ASSERT_NO_THROW(go.draw());
}

TEST(GameObjectTest, CallingSetGameIntanceTwiceWillRaiseLogicError)
{
    auto const g = std::make_shared<MockGame>();
    GameObject go {};
    go.setGameInstance(g);
    ASSERT_THROW(go.setGameInstance(g), std::logic_error);
}

TEST(GameObjectTest, AgeIsZeroByDefault)
{
    GameObject go {};
    ASSERT_EQ(go.getAge(), 0.0f);
}

TEST(GameObjectTest, AgeSetBySetAge)
{
    GameObject go {};
    go.setAge(5000.0f);
    ASSERT_EQ(go.getAge(), 5000.0f);
}

TEST(GameObjectTest, Destroy)
{
    GameObject go {};
    ASSERT_NO_THROW(go.destroy());
}

TEST(GameObjectTest, DefaultName)
{
    GameObject go {};
    ASSERT_EQ(go.getName(), "");
}
class GameObjectTimeParametrizeTestFixture : public ::testing::TestWithParam<float> {
};

TEST_P(GameObjectTimeParametrizeTestFixture, AgeIsIncreasedByUpdate)
{
    auto const elapsed = GetParam();
    GameObject go {};
    go.update(elapsed);
    ASSERT_EQ(go.getAge(), elapsed);
}
INSTANTIATE_TEST_SUITE_P(GameObjectTimeParametrizeTest, GameObjectTimeParametrizeTestFixture,
    ::testing::Values(0.0f, 0.1f, 0.5f, 10.0f, 100.0f, -1.0f));

TEST(GameObjectTest, GetGameReturnsCorrectGamePointer)
{
    auto const g = std::make_shared<MockGame>();
    GameObject go {};
    go.setGameInstance(g);

    ASSERT_EQ(go.getGame(), g);
}

TEST(GameObjectTest, GetGameRaisesExceptionWhenGameIsExpired)
{
    auto g = std::make_shared<MockGame>();
    GameObject go {};
    go.setGameInstance(g);
    // invalidate game
    g.reset();
    ASSERT_THROW(go.getGame(), std::logic_error);
}

#endif
