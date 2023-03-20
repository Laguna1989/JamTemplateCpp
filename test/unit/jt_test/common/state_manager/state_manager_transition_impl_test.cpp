#include <state_manager/state_manager_transition_impl.hpp>
#include <gtest/gtest.h>

class StateManagerTransitionStub : public jt::StateManagerTransitionImpl {
public:
    StateManagerTransitionStub()
        : jt::StateManagerTransitionImpl { 0.00001f }
    {
    }

    bool m_drawCalled { false };
    bool m_updateCalled { false };

private:
    void doUpdate(float /*elapsed*/) override { m_updateCalled = true; }
    void doStart() override { }
    void doDraw(std::shared_ptr<jt::RenderTargetInterface> /*rt*/) override { m_drawCalled = true; }
};

TEST(StateManagerTransitionImplTest, IsInProgressReturnsFalseByDefault)
{
    StateManagerTransitionStub transition;
    ASSERT_FALSE(transition.isInProgress());
}

TEST(StateManagerTransitionImplTest, IsInProgressReturnsTrueAfterStart)
{
    StateManagerTransitionStub transition;
    transition.start();
    ASSERT_TRUE(transition.isInProgress());
}

TEST(StateManagerTransitionImplTest, TriggerStateChangeReturnsFalseByDefault)
{
    StateManagerTransitionStub transition;
    ASSERT_FALSE(transition.triggerStateChange());
}

TEST(StateManagerTransitionImplTest, DrawIsNotCalledWhenNotStarted)
{
    StateManagerTransitionStub transition;
    transition.draw(nullptr);
    ASSERT_FALSE(transition.m_drawCalled);
}

TEST(StateManagerTransitionImplTest, DrawIsCalledWhenStarted)
{
    StateManagerTransitionStub transition;
    transition.start();
    transition.draw(nullptr);
    ASSERT_TRUE(transition.m_drawCalled);
}

TEST(StateManagerTransitionImplTest, UpdateIsNotCalledWhenNotStarted)
{
    StateManagerTransitionStub transition;
    transition.update(0.1f);
    ASSERT_FALSE(transition.m_updateCalled);
}

TEST(StateManagerTransitionImplTest, UpdateIsCalledWhenStarted)
{
    StateManagerTransitionStub transition;
    transition.start();
    transition.update(0.1f);
    ASSERT_TRUE(transition.m_updateCalled);
}

TEST(StateManagerTransitionImplTest, CallUpdateTwice)
{
    StateManagerTransitionStub transition;
    transition.start();
    transition.update(0.1f);
    ASSERT_NO_THROW(transition.update(0.1f););
}

TEST(StateManagerTransitionImplTest, IsInFirstHalfReturnsTrueInitially)
{
    StateManagerTransitionStub transition;
    transition.start();
    ASSERT_TRUE(transition.isInFirstHalf());
}

TEST(StateManagerTransitionImplTest, IsInFirstHalfReturnsFalseAfterUpdate)
{
    StateManagerTransitionStub transition;
    transition.start();
    transition.update(0.1f);
    ASSERT_FALSE(transition.isInFirstHalf());
}

TEST(StateManagerTransitionImplTest, GetRatioReturnsZeroInitially)
{
    StateManagerTransitionStub transition;
    ASSERT_EQ(transition.getRatio(), 0.0f);
}
