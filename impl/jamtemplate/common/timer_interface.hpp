#ifndef GUARD_JAMTEMPLATE_TIMER_INTERFACE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TIMER_INTERFACE_HPP_INCLUDEGUARD

#include <functional>

namespace jt {
class TimerInterface {
public:
    using CallbackType = typename std::function<void(void)>;

    virtual ~TimerInterface() = default;

    /// Get the total time (what is set in the constructor)
    /// \return the total time in seconds
    virtual float getTotalTime() const = 0;

    /// Get the current time
    /// \return the current time in seconds
    virtual float getCurrentTime() const = 0;

    /// Get the time Left until the Timer expires and triggers the callback
    /// \return the time left in seconds
    virtual float getRemainingTime() = 0;

    /// Cancel the timer. The callback will not be invoked.
    virtual void cancel() = 0;

    /// Finish the timer. The callback will be invoked.
    virtual void finish() = 0;

    /// Update the timer
    /// \param elapsed time in seconds
    virtual void updateTimer(float elapsed) = 0;

    /// Set the total time
    /// \param totalTime total time in seconds
    virtual void setTotalTime(float totalTime) = 0;

    /// Set the timer callback
    /// \param cb the callback
    virtual void setCallback(CallbackType cb) = 0;
};
} // namespace jt
#endif // GUARD_JAMTEMPLATE_TIMER_INTERFACE_HPP_INCLUDEGUARD
