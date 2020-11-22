#include "Timer.hpp"
#include "GameObject.hpp"
#include <assert.h>
#include <exception>
#include <iostream>

namespace JamTemplate {

Timer::Timer(float t, Timer::CallbackType cb, int r)
    : m_timer { t }
    , m_callback { std::move(cb) }
    , m_repeat { r }
{
    if (!m_callback) {
        throw std::invalid_argument("Timer callback must be valid!");
    }
}
void Timer::doUpdate(float const /*elapsed*/)
{
    if (getAge() >= m_timer) {
        setAge(0);
        if (isAlive()) {
            // only call the callback if the timer is alive
            assert(m_callback);
            m_callback();
        }
        if (m_repeat < 0) {
            return;
        } else if (m_repeat == 1) {
            kill();
        } else {
            m_repeat--;
        }
    }
}

} // namespace JamTemplate
