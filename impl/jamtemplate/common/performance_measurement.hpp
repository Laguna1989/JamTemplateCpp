#ifndef MYAWESOMEGAME_PERFORMANCE_MEASUREMENT_HPP
#define MYAWESOMEGAME_PERFORMANCE_MEASUREMENT_HPP

#include <chrono>
#include <functional>

float getDurationInSecondsSince(std::chrono::time_point<std::chrono::system_clock> const& since);
float measureTime(std::function<void(void)> const& f);

#endif // MYAWESOMEGAME_PERFORMANCE_MEASUREMENT_HPP
