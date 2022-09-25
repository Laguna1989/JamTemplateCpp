#ifndef JAMTEMPLATE_PERFORMANCE_MEASUREMENT_HPP
#define JAMTEMPLATE_PERFORMANCE_MEASUREMENT_HPP

#include <chrono>
#include <functional>

namespace jt {
/// Helper function to measure time since a time point.
/// \param since start time
/// \return the duration in seconds since the passed value
float getDurationInSecondsSince(std::chrono::time_point<std::chrono::system_clock> const& since);

/// Helper function to measure the time of a specific call.
/// \param the function to be measured
/// \return the duration in seconds
float measureTime(std::function<void(void)> const& f);

} // namespace jt
#endif // JAMTEMPLATE_PERFORMANCE_MEASUREMENT_HPP
