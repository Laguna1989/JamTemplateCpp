#include "timer.hpp"
#include <gtest/gtest.h>

using jt::Timer;

class TimerTimeParametrizedTestFixture : public ::testing::TestWithParam<float> {
};

TEST_P(TimerTimeParametrizedTestFixture, TotalTimeIsSetCorrectly)
{
    auto const time = GetParam();
    Timer t { time, []() {} };
    ASSERT_EQ(t.getTotalTime(), time);
}

TEST_P(TimerTimeParametrizedTestFixture, CurrentTimeIsInitiallyZero)
{
    auto const time = GetParam();
    Timer t { time, []() {} };
    ASSERT_EQ(t.getCurrentTime(), 0.0f);
}

INSTANTIATE_TEST_SUITE_P(TimerTimeParametrizedTest, TimerTimeParametrizedTestFixture,
    ::testing::Values(0.0f, 10.0f, 22.0f));

TEST(TimerTest, CallbackIsNotCalledByDefault)
{
    bool callback_invoked { false };
    Timer t { 10.0f, [&callback_invoked]() { callback_invoked = true; } };
    ASSERT_FALSE(callback_invoked);
}

class TimerFactorParametrizedTestFixture : public ::testing::TestWithParam<float> {
};

TEST_P(TimerFactorParametrizedTestFixture, CurrentTimeIsExpectedValue)
{
    auto const time = 10.0f;
    auto const factor = GetParam();
    Timer t { time, []() {} };

    t.update(factor * time);
    ASSERT_EQ(t.getCurrentTime(), factor * time);
}

TEST_P(TimerFactorParametrizedTestFixture, CallbackIsNotCalledBeforeTimerTime)
{
    auto const time = 10.0f;
    auto const factor = GetParam();
    bool callback_invoked { false };
    Timer t { time, [&callback_invoked]() { callback_invoked = true; } };

    t.update(factor * time);
    ASSERT_FALSE(callback_invoked);
}

TEST_P(TimerFactorParametrizedTestFixture, CallbackIsInvokedAfterTimeIsExceeded)
{
    auto const time = 10.0f;
    auto const factor = GetParam();
    bool callback_invoked { false };
    Timer t { time, [&callback_invoked]() { callback_invoked = true; } };

    t.update((1.0f + factor) * time);
    ASSERT_TRUE(callback_invoked);
}

INSTANTIATE_TEST_SUITE_P(TimerFactorParametrizedTest, TimerFactorParametrizedTestFixture,
    ::testing::Values(0.0f, 0.1f, 0.25f, 0.33333f, 0.5f, 0.9f, 0.999f));

class TimerCountParametrizedTestFixture : public ::testing::TestWithParam<int> {
};

TEST_P(
    TimerCountParametrizedTestFixture, CallbackIsCalledExactlyCalledAsOftenAsSpecifiedInOneUpdate)
{
    auto expected_count = GetParam();
    int callback_count { 0 };
    float const alarmTime = 1.2f;
    Timer t { alarmTime, [&callback_count]() { callback_count++; }, expected_count };

    // second update could possibly trigger callback
    t.update(5000.0f);
    EXPECT_EQ(callback_count, expected_count);
}

TEST_P(TimerCountParametrizedTestFixture,
    CallbackIsCalledExactlyCalledAsOftenAsFittingInTimeInOneUpdate)
{
    auto expected_count = GetParam();
    int callback_count { 0 };
    float const alarmTime = 1.2f;
    Timer t { alarmTime, [&callback_count]() { callback_count++; } };

    // second update could possibly trigger callback
    t.update(alarmTime * expected_count);
    EXPECT_EQ(callback_count, expected_count);
}

TEST_P(TimerCountParametrizedTestFixture,
    CallbackIsCalledExactlyCalledAsOftenAsFittingInTimeInMultipleUpdates)
{
    auto expected_count = GetParam();
    int callback_count { 0 };
    float const alarmTime = 1.2f;
    Timer t { alarmTime, [&callback_count]() { callback_count++; } };

    // second update could possibly trigger callback
    for (int i = 0; i != expected_count; ++i) {
        t.update(alarmTime);
    }
    EXPECT_EQ(callback_count, expected_count);
}

TEST_P(TimerCountParametrizedTestFixture,
    CallbackIsCalledExactlyCalledAsOftenAsSpecifiedInMultipleUpdates)
{
    auto expected_count = GetParam();
    int callback_count { 0 };
    float const alarmTime = 1.9f;
    Timer t { alarmTime, [&callback_count]() { callback_count++; }, expected_count };

    // second update could possibly trigger callback
    for (auto i = 0; i != 5000; ++i) {
        t.update(1.0f);
    }
    EXPECT_EQ(callback_count, expected_count);
}

INSTANTIATE_TEST_SUITE_P(
    TimerCountParametrizedTest, TimerCountParametrizedTestFixture, ::testing::Values(1, 2, 14));

TEST(TimerTest, InvalidCallback)
{
    auto const lambda = []() { Timer const t { 2.5f, nullptr }; };
    EXPECT_THROW(lambda(), std::invalid_argument);
}
