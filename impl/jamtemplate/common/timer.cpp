#include "timer.hpp"
#include <stdexcept>
#include <utility>

namespace jt {

Timer::Timer(float timeInSeconds, Timer::CallbackType cb, int r)
{
    m_repeat = r;
    setTotalTime(timeInSeconds);
    setCallback(cb);
}
void Timer::doUpdate(float const elapsed)
{
    if (!isAlive()) {
        return;
    }
    updateTimer(elapsed);
}

void Timer::invokeCallback()
{
    m_callback();

    if (m_repeat == 1) {
        kill();
    } else {
        m_repeat--;
    }
}
float Timer::getTotalTime() const { return m_totalTime; }
float Timer::getCurrentTime() const { return m_currentTime; }
float Timer::getRemainingTime() { return m_totalTime - m_currentTime; }

void Timer::cancel()
{
    m_currentTime = m_totalTime;
    kill();
}

void Timer::finish()
{
    m_currentTime = m_totalTime;
    invokeCallback();
    kill();
}

void Timer::updateTimer(float elapsed)
{
    m_currentTime += elapsed;
    if (elapsed >= m_totalTime) {
        int const count = static_cast<int>(elapsed / m_totalTime);
        for (int i = 0; i != count; ++i) {
            invokeCallback();
            if (!isAlive()) {
                break;
            }
        }
    } else {
        if (m_currentTime >= m_totalTime) {
            m_currentTime -= m_totalTime;
            invokeCallback();
        }
    }
}

void Timer::setTotalTime(float totalTime) { m_totalTime = totalTime; }
void Timer::setCallback(TimerInterface::CallbackType cb)
{
    if (!cb) {
        throw std::invalid_argument("Timer callback must be valid!");
    }
    m_callback = cb;
}

} // namespace jt
