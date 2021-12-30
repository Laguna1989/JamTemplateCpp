#include "game_object.hpp"
#include "game_state.hpp"
#include "mocks/mock_game.hpp"
#include "mocks/mock_object.hpp"
#include "mocks/mock_tween.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>

using jt::GameObject;
using jt::GameState;
using ::testing::_;

#ifndef JT_ENABLE_WEB
class GameStateImpl : public GameState {
public:
    std::string getName() const override { return "GameStateImpl"; }

private:
    virtual void doInternalDraw() const override { }
    virtual void doInternalCreate() override { }
    virtual void doInternalUpdate(float /*elapsed*/) override { }
};

class GamestateInitialTest : public ::testing::Test {
protected:
    GameStateImpl gamestate {};
};

TEST_F(GamestateInitialTest, Alive) { ASSERT_TRUE(gamestate.isAlive()); }

TEST_F(GamestateInitialTest, Age) { ASSERT_FLOAT_EQ(gamestate.getAge(), 0.0f); }

TEST_F(GamestateInitialTest, NumberOfObjects) { ASSERT_EQ(gamestate.getNumberOfObjects(), 0); }

TEST_F(GamestateInitialTest, NotInitialized) { ASSERT_FALSE(gamestate.hasBeenInitialized()); }

TEST_F(GamestateInitialTest, CreateWithoutGameInstance) { ASSERT_ANY_THROW(gamestate.create()); }

TEST_F(GamestateInitialTest, InitialAutoUpdateObjects)
{
    ASSERT_TRUE(gamestate.getAutoUpdateObjects());
}

TEST_F(GamestateInitialTest, InitialAutoUpdateTweens)
{
    ASSERT_TRUE(gamestate.getAutoUpdateTweens());
}

TEST_F(GamestateInitialTest, InitialAutoDraw) { ASSERT_TRUE(gamestate.getAutoDraw()); }

class GameStateTest : public ::testing::Test {
public:
    std::shared_ptr<MockGame> game;
    GameStateImpl gamestate;
    std::shared_ptr<MockObject> mockObject;
    MockGfx gfx;
    MockWindow window;
    void SetUp() override
    {
        game = std::make_shared<MockGame>();
        ON_CALL(*game, gfx).WillByDefault(::testing::ReturnRef(gfx));
        ON_CALL(gfx, window).WillByDefault(::testing::ReturnRef(window));
        gamestate.setGameInstance(game);
    }
    void AddGameObject()
    {
        mockObject = std::make_shared<MockObject>();
        EXPECT_CALL(*mockObject, doCreate());
        gamestate.add(mockObject);
    }
};

TEST_F(GameStateTest, SetGameInstance) { ASSERT_EQ(game, gamestate.getGame()); }

TEST_F(GameStateTest, CreateWithGameInstance) { ASSERT_NO_THROW(gamestate.create()); }

TEST_F(GameStateTest, AddGameObject)
{
    auto mo = std::make_shared<MockObject>();
    EXPECT_CALL(*mo, doCreate());
    gamestate.add(mo);
    ASSERT_EQ(gamestate.getNumberOfObjects(), 1);
}

TEST_F(GameStateTest, DrawCallsDrawOnAddedGameObjects)
{
    AddGameObject();

    EXPECT_CALL(*mockObject, doDraw());
    gamestate.draw();
}

TEST_F(GameStateTest, UpdateCallsUpdateOnAddedGameObjects)
{
    AddGameObject();

    auto const delta = 0.75f;
    EXPECT_CALL(*mockObject, doUpdate(delta));
    gamestate.update(delta);
}

TEST_F(GameStateTest, GameObjectList)
{
    auto const N = 500U;
    std::vector<std::weak_ptr<MockObject>> objects;
    for (auto i = 0U; i != N; ++i) {
        auto mo = std::make_shared<MockObject>();
        EXPECT_CALL(*mo, doCreate());
        gamestate.add(mo);
        objects.push_back(mo);
        EXPECT_CALL(*mo, doUpdate(_));
    }
    // multiple objects are added initially only in next update call
    gamestate.update(0.0f);
    EXPECT_EQ(gamestate.getNumberOfObjects(), N);

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
    gamestate.update(0.0f);
    EXPECT_EQ(gamestate.getNumberOfObjects(), N / 2);
}

TEST_F(GameStateTest, NoAutoUpdateObjects)
{
    auto mo = std::make_shared<MockObject>();
    EXPECT_CALL(*mo, doCreate());
    gamestate.add(mo);

    // update
    gamestate.setAutoUpdateObjects(false);
    EXPECT_CALL(*mo, doUpdate(0.1f)).Times(0);
    gamestate.update(0.1f);
}

TEST_F(GameStateTest, NoAutoDrawAfterSet)
{
    auto mo = std::make_shared<MockObject>();
    EXPECT_CALL(*mo, doCreate());
    gamestate.add(mo);

    auto const delta = 0.75f;
    EXPECT_CALL(*mo, doUpdate(delta));
    gamestate.update(delta);

    gamestate.setAutoDraw(false);
    EXPECT_CALL(*mo, doDraw()).Times(0);
    gamestate.draw();
}

TEST_F(GameStateTest, AutoUpdateObjectsAfterSet)
{
    gamestate.setAutoUpdateObjects(false);
    ASSERT_FALSE(gamestate.getAutoUpdateObjects());
}

TEST_F(GameStateTest, AutoUpdateTweensAfterSet)
{
    gamestate.setAutoUpdateTweens(false);
    ASSERT_FALSE(gamestate.getAutoUpdateTweens());
}

TEST_F(GameStateTest, AutoDrawAfterSet)
{
    gamestate.setAutoDraw(false);
    ASSERT_FALSE(gamestate.getAutoDraw());
}

TEST_F(GameStateTest, AddGameObjectToTwoStatesWillRaiseException)
{
    auto g = std::make_shared<::testing::NiceMock<MockGame>>();
    GameStateImpl gamestate1;
    gamestate1.setGameInstance(g);

    GameStateImpl gamestate2;
    gamestate2.setGameInstance(g);

    auto obj = std::make_shared<MockObject>();

    EXPECT_CALL(*obj, doCreate());

    gamestate1.add(obj);
    ASSERT_THROW(gamestate2.add(obj), std::logic_error);
}

TEST_F(GameStateTest, RemovalOfGameObjectWillCallDoDestroyOnGameObject)
{
    AddGameObject();

    mockObject->kill();
    EXPECT_CALL(*mockObject, doDestroy());
    gamestate.update(0.1f);
    ASSERT_EQ(gamestate.getNumberOfObjects(), 0U);
}

#endif
