#include "GameState.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "MockObject.hpp"
#include "MockTween.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using jt::Game;
using jt::GameObject;
using jt::GameState;
using ::testing::_;

TEST(GameStateInitTest, InitialValues)
{
    GameState s {};
    EXPECT_NEAR(s.getAge(), 0.0f, 0.001f);
    EXPECT_EQ(s.getNumberOfObjects(), 0);
    EXPECT_FALSE(s.hasBeenInitialized());
    EXPECT_TRUE(s.isAlive());
}

TEST(GameStateInitTest, Create)
{
    GameState s {};
    EXPECT_NO_THROW(s.create());
}

class GameStateTest : public ::testing::Test {
public:
    std::shared_ptr<Game> g;
    GameState s;
    void SetUp() override
    {
        g = std::make_shared<Game>(1, 1, 1.0f, "");
        EXPECT_THROW(s.getGame(), std::exception);
        s.setGameInstance(g);
        EXPECT_NO_THROW(s.getGame());
    }
};

TEST_F(GameStateTest, SetGameInstance)
{
    auto const g2 = s.getGame();
    EXPECT_NE(g2, nullptr);
    EXPECT_EQ(g, g2);
}

TEST_F(GameStateTest, CallsToGameObjects)
{
    ASSERT_EQ(s.getNumberOfObjects(), 0);

    auto mo = std::make_shared<MockObject>();
    EXPECT_CALL(*mo, doCreate());
    s.add(mo);
    EXPECT_EQ(s.getNumberOfObjects(), 1);

    // update
    auto const delta = 0.75f;
    EXPECT_CALL(*mo, doUpdate(delta));
    s.update(delta);
    EXPECT_NEAR(mo->getAge(), delta, 0.001f);

    // draw
    EXPECT_CALL(*mo, doDraw());
    s.draw();
}

TEST_F(GameStateTest, GameObjectList)
{
    auto const N = 500U;
    std::vector<std::weak_ptr<MockObject>> objects;
    for (auto i = 0U; i != N; ++i) {
        auto mo = std::make_shared<MockObject>();
        EXPECT_CALL(*mo, doCreate());
        s.add(mo);
        objects.push_back(mo);
        EXPECT_CALL(*mo, doUpdate(_));
    }
    // multiple objects are added initially only in next update call
    s.update(0.0f);
    EXPECT_EQ(s.getNumberOfObjects(), N);

    // kill half the objects
    for (auto i = 0U; i != N; ++i) {
        auto mo = objects.at(i);

        bool designate_object_for_kill = static_cast<bool>(i % 2 == 1);
        if (designate_object_for_kill) {
            mo.lock()->kill();
        } else {
            EXPECT_CALL(*mo.lock(), doUpdate(_));
        }
    }
    // Update will clean up all killed gameobjects
    s.update(0.0f);
    EXPECT_EQ(s.getNumberOfObjects(), N / 2);
}

TEST_F(GameStateTest, CallsToTween)
{
    auto obj = std::make_shared<int>(5);
    auto wp = std::weak_ptr<int> { obj };
    auto tw = std::make_shared<MockTween<int>>(
        wp, [](auto /*obj*/, auto /*elapsed*/) { return true; }, 1.0f);
    // state needs to be initialized to work
    s.create();

    // add tween
    s.add(tw);

    EXPECT_CALL(*tw, doUpdate(_));
    // update state
    s.update(0.1f);
}
