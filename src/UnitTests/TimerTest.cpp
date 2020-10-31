
#include "../JamTemplate/Timer.hpp"
#include "gtest/gtest.h"
#include <limits>
#include <utility>

using JamTemplate::Timer;

TEST(TimerTest, TimerIsCalledRepeatedly)
{
    bool callback_invoked { false };
    float const alarmTime = 10.0f;
    Timer t { alarmTime, [&callback_invoked]() { callback_invoked = true; } };

    t.update(alarmTime / 2);
    EXPECT_FALSE(callback_invoked);
    t.update(alarmTime / 2 + 0.1f);
    EXPECT_TRUE(callback_invoked);

    callback_invoked = false;
    ASSERT_FALSE(callback_invoked);

    // timer is set to trigger multiple times, so another call will set callback_invoked to true
    // again.
    t.update(std::numeric_limits<float>::max());
    EXPECT_TRUE(callback_invoked);
}

TEST(TimerTest, TimerIsCalledOnlyOnce)
{
    bool callback_invoked { false };
    float const alarmTime = 10.0f;
    Timer t { alarmTime, [&callback_invoked]() { callback_invoked = true; }, 1 };

    t.update(alarmTime / 2);
    EXPECT_FALSE(callback_invoked);
    t.update(alarmTime / 2 + 0.1f);
    EXPECT_TRUE(callback_invoked);

    callback_invoked = false;
    ASSERT_FALSE(callback_invoked);

    // timer is set to trigger multiple times, so another call will set callback_invoked to true
    // again.
    t.update(std::numeric_limits<float>::max());
    EXPECT_FALSE(callback_invoked);
}

TEST(TimerTest, InvalidCallback)
{
    auto const lambda = []() { Timer const t { 2.5f, nullptr }; };

    EXPECT_THROW(lambda(), std::invalid_argument);
}
