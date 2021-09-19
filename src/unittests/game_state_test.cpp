#include "game_object.hpp"
#include "game_state.hpp"
#include "mocks/mock_game.hpp"
#include "mocks/mock_object.hpp"
#include "mocks/mock_tween.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using jt::GameObject;
using jt::GameState;
using ::testing::_;

#ifndef ENABLE_WEB
class GameStateImpl : public GameState {
private:
    virtual void doInternalDraw() const override { }
    virtual void doInternalCreate() override { }
    virtual void doInternalUpdate(float /*elapsed*/) override { }
};

class GamestateInitialTest : public ::testing::Test {
protected:
    GameStateImpl s {};
};

TEST_F(GamestateInitialTest, Alive) { ASSERT_TRUE(s.isAlive()); }
TEST_F(GamestateInitialTest, Age) { ASSERT_FLOAT_EQ(s.getAge(), 0.0f); }
TEST_F(GamestateInitialTest, NumberOfObjects) { ASSERT_EQ(s.getNumberOfObjects(), 0); }
TEST_F(GamestateInitialTest, NotInitialized) { ASSERT_FALSE(s.hasBeenInitialized()); }
TEST_F(GamestateInitialTest, CreateWithoutGameInstance) { EXPECT_ANY_THROW(s.create()); }
TEST_F(GamestateInitialTest, InitialAutoUpdateObjects) { ASSERT_TRUE(s.getAutoUpdateObjects()); }
TEST_F(GamestateInitialTest, InitialAutoUpdateTweens) { ASSERT_TRUE(s.getAutoUpdateTweens()); }
TEST_F(GamestateInitialTest, InitialAutoDraw) { ASSERT_TRUE(s.getAutoDraw()); }

class GameStateTest : public ::testing::Test {
public:
    std::shared_ptr<jt::GameInterface> g;
    GameStateImpl s;
    std::shared_ptr<MockObject> mo;
    void SetUp() override
    {
        EXPECT_THROW(s.getGame(), std::exception);

        g = std::make_shared<MockGame>();
        s.setGameInstance(g);
        EXPECT_NO_THROW(s.getGame());
    }
    void AddGameObject()
    {
        mo = std::make_shared<MockObject>();
        EXPECT_CALL(*mo, doCreate());
        s.add(mo);
    }
};

TEST_F(GameStateTest, SetGameInstance) { ASSERT_EQ(g, s.getGame()); }

TEST_F(GameStateTest, CreateWithGameInstance) { EXPECT_NO_THROW(s.create()); }

TEST_F(GameStateTest, AddGameObject)
{
    ASSERT_EQ(s.getNumberOfObjects(), 0);

    auto mo = std::make_shared<MockObject>();
    EXPECT_CALL(*mo, doCreate());
    s.add(mo);
    EXPECT_EQ(s.getNumberOfObjects(), 1);
}

TEST_F(GameStateTest, CallsToGameObjects)
{
    AddGameObject();

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

TEST_F(GameStateTest, NoAutoUpdateTween)
{
    auto obj = std::make_shared<int>(5);
    auto wp = std::weak_ptr<int> { obj };
    auto tw = std::make_shared<MockTween<int>>(
        wp, [](auto /*obj*/, auto /*elapsed*/) { return true; }, 1.0f);
    // state needs to be initialized to work
    s.create();

    // add tween
    s.add(tw);

    s.setAutoUpdateTweens(false);

    EXPECT_CALL(*tw, doUpdate(_)).Times(0);
    // update state
    s.update(0.1f);
}

TEST_F(GameStateTest, NoAutoUpdateObjects)
{
    auto mo = std::make_shared<MockObject>();
    EXPECT_CALL(*mo, doCreate());
    s.add(mo);

    // update
    s.setAutoUpdateObjects(false);
    EXPECT_CALL(*mo, doUpdate(0.1f)).Times(0);
    s.update(0.1f);
}

TEST_F(GameStateTest, NoAutoDrawAfterSet)
{
    auto mo = std::make_shared<MockObject>();
    EXPECT_CALL(*mo, doCreate());
    s.add(mo);

    auto const delta = 0.75f;
    EXPECT_CALL(*mo, doUpdate(delta));
    s.update(delta);

    s.setAutoDraw(false);
    EXPECT_CALL(*mo, doDraw()).Times(0);
    s.draw();
}

TEST_F(GameStateTest, AutoUpdateObjectsAfterSet)
{
    s.setAutoUpdateObjects(false);
    ASSERT_FALSE(s.getAutoUpdateObjects());
}

TEST_F(GameStateTest, AutoUpdateTweensAfterSet)
{
    s.setAutoUpdateTweens(false);
    ASSERT_FALSE(s.getAutoUpdateTweens());
}

TEST_F(GameStateTest, AutoDrawAfterSet)
{
    s.setAutoDraw(false);
    ASSERT_FALSE(s.getAutoDraw());
}

#endif
