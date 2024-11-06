#ifndef JAMTEMPLATE_PERFORMANCE_MEASUREMENT_HPP
#define JAMTEMPLATE_PERFORMANCE_MEASUREMENT_HPP

#include <nlohmann.hpp>
#include <chrono>
#include <functional>
#include <string>
#include <thread>

namespace jt {

/// Helper function to measure time since a time point.
/// \param since start time
/// \return the duration in seconds since the passed value
float getDurationInSecondsSince(std::chrono::time_point<std::chrono::steady_clock> const& since);

/// Generic Template to allow for partial specialization. Specialization is needed for void return
/// type.
template <typename>
struct MeasureTimeGeneric;

/// Helper Object that allows to measure execution time for an arbitrary function.
///
/// Note: Calling the function multiple times will add up the execution time
///
/// \tparam R return value type of the function to be measured
/// \tparam Args arguments type of the function to be measured
template <typename R, typename... Args>
struct MeasureTimeGeneric<R(Args...)> {
    /// Constructor
    /// \param func the function to be measured
    explicit MeasureTimeGeneric(std::function<R(Args...)> const& func)
        : m_func(func)
        , m_elapsedTimeInSeconds { 0.0f }
    {
    }

    /// Call operator for the measurement
    /// \param args arguments to be passed to the function to be measured
    /// \return the return value of the function to be measured
    R operator()(Args... args) const
    {
        auto const start = std::chrono::steady_clock::now();
        R const result = m_func(args...);
        m_elapsedTimeInSeconds += getDurationInSecondsSince(start);
        return result;
    }

    /// Get the accumulated elapsed time of all function calls
    /// \return elapsed time in seconds
    float getElapsedTimeInSeconds() const noexcept { return m_elapsedTimeInSeconds; }

    /// reset the timer
    void resetTimer() noexcept { m_elapsedTimeInSeconds = 0.0f; }

private:
    std::function<R(Args...)> m_func;
    mutable float m_elapsedTimeInSeconds;
};

/// Helper Object that allows to measure execution time for an arbitrary function. Specialization
/// for void return type.
///
/// Note: Calling the function multiple times will add up the execution time
/// \tparam R return value type of the function to be measured
/// \tparam Args arguments type of the function to be measured
template <typename... Args>
struct MeasureTimeGeneric<void(Args...)> {
    /// Constructor
    /// \param func the function to be measured
    explicit MeasureTimeGeneric(std::function<void(Args...)> const& func)
        : m_func(func)
        , m_elapsedTimeInSeconds { 0.0f }
    {
    }

    /// Call operator for the measurement
    /// \param args arguments to be passed to the function to be measured
    /// \return the return value of the function to be measured
    void operator()(Args... args) const
    {
        auto const start = std::chrono::steady_clock::now();
        m_func(args...);
        m_elapsedTimeInSeconds += getDurationInSecondsSince(start);
    }

    /// Get the accumulated elapsed time of all function calls
    /// \return elapsed time in seconds
    float getElapsedTimeInSeconds() const noexcept { return m_elapsedTimeInSeconds; }

    /// reset the timer

    void resetTimer() noexcept { m_elapsedTimeInSeconds = 0.0f; }

private:
    std::function<void(Args...)> m_func;
    mutable float m_elapsedTimeInSeconds;
};

/// Helper function to create a generic TimeMeasurement object
///
/// Note: This function is just here for convenience. Class template arguments are mandatory,
/// function template arguments are not. This allows to omit the template arguments when
/// constructing the MeasureTimeGeneric object. Note: This needs to be called with std::function
/// type, a plain lambda will not work.
///
/// \tparam R return value type of the function to be measured
/// \tparam Args arguments type of the function to be measured
/// \param func the function to be measured
/// \return TimeMeasureGeneric
template <typename R, typename... Args>
auto makeMeasureTimeGeneric(std::function<R(Args...)> const& func)
{
    return MeasureTimeGeneric<R(Args...)> { func };
}
} // namespace jt

#endif // JAMTEMPLATE_PERFORMANCE_MEASUREMENT_HPP
