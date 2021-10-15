#include "game_test.hpp"
#include "mocks/mock_state.hpp"
#include "render_window.hpp"

using ::testing::NiceMock;

TEST_F(GameTest, InitialValues) { ASSERT_EQ(g->getRenderTarget(), nullptr); }

TEST_F(GameTest, DrawWithNoState) { ASSERT_NO_THROW(g->draw()); }

TEST_F(GameTest, GameUpdateWithoutState) { g->update(0.01f); }

TEST_F(GameTest, GameUpdateCallsStateUpdateForActiveState)
{
    auto ms = std::make_shared<MockState>();
    EXPECT_CALL(*ms, doInternalCreate());
    g->switchState(ms);

    float expected_update_time = 0.05f;
    EXPECT_CALL(*ms, doInternalUpdate(expected_update_time));
    g->update(expected_update_time);
}

TEST_F(GameTest, SwitchToNullptrState)
{
    ASSERT_THROW(g->switchState(nullptr), std::invalid_argument);
}

TEST_F(GameTest, SetNullptrRendertarget)
{
    ASSERT_THROW(g->setRenderTarget(nullptr), std::invalid_argument);
}

TEST_F(GameTest, SwitchStateTwice)
{
    auto ms1 = std::make_shared<NiceMock<MockState>>();
    auto ms2 = std::make_shared<NiceMock<MockState>>();

    g->switchState(ms1);

    float expected_update_time = 0.05f;
    g->update(expected_update_time);

    g->draw();
    g->switchState(ms2);

    // first update is required to switch the state
    g->update(0.0f);
    // second update will actually call the new state update
    g->update(expected_update_time);

    g->draw();
}

TEST_F(GameTest, SetRenderTargetInvalid)
{
    ASSERT_THROW(g->setRenderTarget(nullptr), std::invalid_argument);
}

TEST_F(GameTest, GetCurrentStateNullptr) { EXPECT_EQ(g->getCurrentState(), nullptr); }

TEST_F(GameTest, GetCurrentStateNonNullptr)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NE(g->getCurrentState(), nullptr);
}

TEST_F(GameTest, GetCurrentStateNonNullptrAfterUpdate)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    g->update(0.1f);
    g->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NE(g->getCurrentState(), nullptr);
}

TEST_F(GameTest, GetCurrentStateAfterSwitch)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->run());
    ASSERT_NE(g->getCurrentState(), nullptr);
}

TEST_F(GameTest, GetCurrentStateAfterSwitchWithoutRun)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NE(g->getCurrentState(), nullptr);
}

TEST_F(GameTest, RunWithOutState) { EXPECT_NO_THROW(g->run()); }

TEST_F(GameTest, RunWithState)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->run());
    ASSERT_NO_THROW(g->run());
}

TEST_F(GameTest, RunWithTwoStates)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->run());
    ASSERT_NO_THROW(g->run());
    g->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->run());
    ASSERT_NO_THROW(g->run());
}

TEST_F(GameTest, StartGameWithOneIteration)
{
    EXPECT_CALL(*window, isOpen)
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));
    auto s = std::make_shared<NiceMock<MockState>>();
    g->startGame(s, []() {});
}

TEST_F(GameTest, GetMusicPlayer) { ASSERT_EQ(g->getMusicPlayer(), nullptr); }

TEST_F(GameTest, GameRunWithStateThrowingStdException)
{
    g->update(0.01f);
    auto state = std::make_shared<MockState>();
    EXPECT_CALL(*state, doInternalCreate());
    EXPECT_CALL(*state, doInternalUpdate(::testing::_))
        .WillOnce(::testing::Invoke([](auto /*elapsed*/) {
            throw std::invalid_argument { "deliberately raise exception." };
        }));
    g->switchState(state);
    ASSERT_THROW(g->run(), std::invalid_argument);
}

TEST_F(GameTest, GetCurrentStateDirectlyAfterSwitch)
{
    auto state1 = std::make_shared<MockState>();
    g->switchState(state1);
    ASSERT_EQ(g->getCurrentState(), state1);
}

TEST_F(GameTest, GameRunWithStateThrowingIntException)
{
    g->update(0.01f);
    auto state = std::make_shared<MockState>();
    EXPECT_CALL(*state, doInternalCreate());
    ON_CALL(*state, doInternalUpdate(::testing::_))
        .WillByDefault(::testing::Invoke([](auto /*elapsed*/) { throw int { 5 }; }));
    g->switchState(state);
    ASSERT_THROW(g->run(), int);
}

TEST_F(GameTest, GetRenderWindowDoesNotReturnNullptr) { ASSERT_NE(g->getRenderWindow(), nullptr); }

TEST_F(GameTest, SwitchStateCallsCameraReset)
{
    EXPECT_CALL(*camera, reset());
    auto state = std::make_shared<MockState>();
    g->switchState(state);
}

TEST_F(GameTest, GetCameraReturnsCorrectPointer) { ASSERT_EQ(g->getCamera(), camera); }

TEST(GameTestWithOutSetup, CreateWithNullptrCamera)
{
    auto window = std::make_shared<::testing::NiceMock<MockWindow>>();
    // getSize has to be called, so that the game knows how big the rendertarget will be.
    ON_CALL(*window, getSize()).WillByDefault([]() { return jt::Vector2 { 100.0f, 200.0f }; });

    auto input = std::make_shared<::testing::NiceMock<MockInput>>();

    auto g = std::make_shared<jt::Game>(window, 1.0f, input, nullptr, nullptr);
}
