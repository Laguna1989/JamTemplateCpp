#include "performance_measurement.hpp"
#include <nlohmann.hpp>
#include <sstream>
#include <thread>

float jt::getDurationInSecondsSince(std::chrono::time_point<std::chrono::steady_clock> const& since)
{
    auto const now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - since).count() / 1000.0f
        / 1000.0f;
}

std::string to_string(std::thread::id id)
{
    std::stringstream ss;
    ss << id;
    return ss.str();
}
