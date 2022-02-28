#include "performance_measurement.hpp"

float getDurationInSecondsSince(std::chrono::time_point<std::chrono::system_clock> const& since)
{
    auto const now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - since).count() / 1000.0f
        / 1000.0f;
}

float measureTime(std::function<void(void)> const& f)
{
    auto const start = std::chrono::system_clock::now();
    f();
    return getDurationInSecondsSince(start);
}
