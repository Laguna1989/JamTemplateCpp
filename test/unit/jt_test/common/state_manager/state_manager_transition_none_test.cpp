#include <mocks/render_target_stub.hpp>
#include <state_manager/state_manager_transition_none.hpp>
#include <gtest/gtest.h>

TEST(StateManagerTransitionNoneTest, IsInProgressReturnsFalse)
{
    jt::StateManagerTransitionNone transition;
    ASSERT_FALSE(transition.isInProgress());
}

TEST(StateManagerTransitionNoneTest, DrawDoesNotThrow)
{
    jt::StateManagerTransitionNone transition;
    RenderTargetStub renderTarget;
    ASSERT_NO_THROW(transition.draw(renderTarget));
}
