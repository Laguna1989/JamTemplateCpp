#include "timer.hpp"
#include <stdexcept>
#include <utility>

jt::Timer::Timer(float timeInSeconds, jt::Timer::CallbackType cb, int r)
{
    m_repeat = r;
    setTotalTime(timeInSeconds);
    setCallback(cb);
}

void jt::Timer::doUpdate(float const elapsed)
{
    if (!isAlive()) {
        return;
    }
    updateTimer(elapsed);
}

void jt::Timer::invokeCallback()
{
    m_callback();

    if (m_repeat == 1) {
        kill();
    } else {
        m_repeat--;
    }
}

float jt::Timer::getTotalTime() const noexcept { return m_totalTime; }

float jt::Timer::getCurrentTime() const noexcept { return m_currentTime; }

float jt::Timer::getRemainingTime() const noexcept { return m_totalTime - m_currentTime; }

void jt::Timer::cancel()
{
    m_currentTime = m_totalTime;
    kill();
}

void jt::Timer::finish()
{
    m_currentTime = m_totalTime;
    invokeCallback();
    kill();
}

void jt::Timer::updateTimer(float elapsed)
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

void jt::Timer::setTotalTime(float totalTime) noexcept { m_totalTime = totalTime; }

void jt::Timer::setCallback(jt::TimerInterface::CallbackType cb)
{
    if (!cb) {
        throw std::invalid_argument("Timer callback must be valid!");
    }
    m_callback = cb;
}
