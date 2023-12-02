#include <performance_measurement.hpp>
#include <gtest/gtest.h>
#include <thread>

namespace {

std::function myAdd = [](double a, double b) {
    std::this_thread::sleep_for(std::chrono::milliseconds { 100 });
    return a + b;
};

std::function myPrinter = [](std::string const& str) {
    std::this_thread::sleep_for(std::chrono::milliseconds { 100 });
    std::cout << str << std::endl;
};

} // namespace

TEST(PerformanceMeasurementGeneric, ReturnsCorrectResult)
{
    auto const measure = jt::makeMeasureTimeGeneric(myAdd);
    ASSERT_EQ(measure(2.0, 3.0), 5.0f);
}

TEST(PerformanceMeasurementGeneric, CanBeCalledWithCapturingLambda)
{
    int x = 0;
    std::function<int(int, int)> const myFunction = [&x](int a, int b) {
        x = a;
        return a + b;
    };
    auto const measure = jt::makeMeasureTimeGeneric(myFunction);
    ASSERT_EQ(measure(2, 3), 5);
}

TEST(PerformanceMeasurementGeneric, MeasuresAtLeastTheDurationOfSleepForOneInvocation)
{
    auto const measure = jt::makeMeasureTimeGeneric(myAdd);

    (void)measure(2.0, 3.0);
    ASSERT_GE(measure.getElapsedTimeInSeconds(), 0.1f);
}

TEST(PerformanceMeasurementGeneric, MeasuresAtLeastTheDurationOfSleepForTwoInvocations)
{
    auto const measure = jt::makeMeasureTimeGeneric(myAdd);

    (void)measure(2.0, 3.0);
    (void)measure(5.0, 3.0);
    ASSERT_GE(measure.getElapsedTimeInSeconds(), 0.2f);
}

TEST(PerformanceMeasurementGeneric, ResetSetsTimerToZero)
{
    auto measure = jt::makeMeasureTimeGeneric(myAdd);

    (void)measure(2.0, 3.0);
    ASSERT_NE(measure.getElapsedTimeInSeconds(), 0.0f);
    (void)measure.resetTimer();
    ASSERT_EQ(measure.getElapsedTimeInSeconds(), 0.0f);
}

TEST(PerformanceMeasurementGeneric, MeasuresAtLeastTheDurationOfSleepForTwoInvocationsAndReset)
{
    auto measure = jt::makeMeasureTimeGeneric(myAdd);

    (void)measure(2.0, 3.0);
    (void)measure.getElapsedTimeInSeconds();
    (void)measure.resetTimer();

    (void)measure(5.0, 3.0);
    ASSERT_GE(measure.getElapsedTimeInSeconds(), 0.1f);
}

TEST(PerformanceMeasurementGeneric, MeasureTimeOfVoidFunction)
{
    auto const measure = jt::makeMeasureTimeGeneric(myPrinter);

    measure("test string");
    ASSERT_GE(measure.getElapsedTimeInSeconds(), 0.1f);
}

TEST(PerformanceMeasurementGeneric, MeasureTimeOfVoidFunctionWithReset)
{
    auto measure = jt::makeMeasureTimeGeneric(myPrinter);

    measure("test string");
    measure.resetTimer();
    ASSERT_EQ(measure.getElapsedTimeInSeconds(), 0.0f);
}
