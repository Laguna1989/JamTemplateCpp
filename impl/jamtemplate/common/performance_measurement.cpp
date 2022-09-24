#include "performance_measurement.hpp"

float jt::getDurationInSecondsSince(std::chrono::time_point<std::chrono::system_clock> const& since)
{
    auto const now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - since).count() / 1000.0f
        / 1000.0f;
}

/// TODO change to template F&& f
float jt::measureTime(std::function<void(void)> const& f)
{
    auto const start = std::chrono::system_clock::now();
    /// TODO use invoke
    f();
    return jt::getDurationInSecondsSince(start);
}
