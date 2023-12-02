#ifndef JAMTEMPLATE_TIMER_HPP
#define JAMTEMPLATE_TIMER_HPP

#include <game_object.hpp>
#include <timer_interface.hpp>

namespace jt {

/// Timer class
class Timer : public GameObject, public TimerInterface {
public:
    /// Constructor
    /// \param timeInSeconds how long until the callback is invoked (in seconds)
    /// \param cb callback
    /// \param r number of repetitions (-1 means infinite)
    Timer(float timeInSeconds, CallbackType cb, int r = -1);

    /// Timer is move-able and not copy-able
    Timer(Timer const&) = delete;
    Timer(Timer&&) = default;

    /// Timer is move-assign-able and not copy-assign-able
    Timer operator=(Timer const&) = delete;
    Timer& operator=(Timer&&) = default;

    float getTotalTime() const noexcept override;
    void updateTimer(float elapsed) override;
    void setTotalTime(float totalTime) noexcept override;
    void setCallback(CallbackType cb) override;

    float getCurrentTime() const noexcept override;

    float getRemainingTime() const noexcept override;

    void cancel() override;

    void finish() override;

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
