#ifndef GUARD_JAMTEMPLATE_TIMER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TIMER_HPP_INCLUDEGUARD

#include "game_object.hpp"
#include <functional>

namespace jt {

/// Timer class
class Timer : public GameObject {
public:
    using CallbackType = std::function<void(void)>;
    /// Constructor
    /// \param timeInSeconds how long until the callback is invoked (in seconds)
    /// \param cb callback
    /// \param r number of repetitions (-1 means infinite)
    Timer(float timeInSeconds, CallbackType cb, int r = -1);

    /// Timer is not copy-able and not move-able
    Timer(Timer const&) = delete;
    Timer(Timer&&) = delete;

    /// Timer is not copy-assign-able and not move-assign-able
    Timer operator=(Timer const&) = delete;
    Timer& operator=(Timer&&) = delete;

    /// Get the total time (what is set in the constructor)
    /// \return the total time
    float getTotalTime() const;

    /// Get the current time
    /// \return
    float getCurrentTime() const;

private:
    float m_totalTime { 0.0f };
    float m_currentTime { 0.0f };

    CallbackType m_callback {};
    int m_repeat { 1 };

    virtual void doUpdate(float const /*elapsed*/) override;
    void invokeCallback();
};
} // namespace jt
#endif
