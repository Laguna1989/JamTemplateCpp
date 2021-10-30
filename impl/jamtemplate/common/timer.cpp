#include "timer.hpp"
#include <stdexcept>
#include <utility>

namespace jt {

Timer::Timer(float timeInSeconds, Timer::CallbackType cb, int r)
    : m_totalTime { timeInSeconds }
    , m_callback { std::move(cb) }
    , m_repeat { r }
{
    if (!m_callback) {
        throw std::invalid_argument("Timer callback must be valid!");
    }
}
void Timer::doUpdate(float const elapsed)
{
    if (!isAlive()) {
        return;
    }
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

} // namespace jt
