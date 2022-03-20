#ifndef GUARD_JAMTEMPLATE_PERFORMANCE_MEASUREMENT_HPP
#define GUARD_JAMTEMPLATE_PERFORMANCE_MEASUREMENT_HPP

#include <chrono>
#include <functional>

namespace jt {
float getDurationInSecondsSince(std::chrono::time_point<std::chrono::system_clock> const& since);
float measureTime(std::function<void(void)> const& f);

} // namespace jt
#endif // GUARD_JAMTEMPLATE_PERFORMANCE_MEASUREMENT_HPP
