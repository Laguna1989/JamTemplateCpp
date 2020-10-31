#ifndef JAMTEMPLATE_TIMER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TIMER_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include <assert.h>
#include <exception>
#include <functional>
#include <iostream>

namespace JamTemplate {

// forward declaration
class Game;

class Timer : public GameObject {
public:
    using CallbackType = std::function<void(void)>;
    Timer(float t, CallbackType cb, int r = -1)
        : m_timer { t }
        , m_callback { std::move(cb) }
        , m_repeat { r }
    {
        if (!m_callback) {
            throw std::invalid_argument("Timer callback must be valid!");
        }
    }

    /// Timer is not copy-able and not move-able
    Timer(Timer const&) = delete;
    Timer(Timer&&) = delete;

    /// Timer is not copy-assign-able and not move-assign-able
    Timer operator=(Timer const&) = delete;
    Timer& operator=(Timer&&) = delete;

private:
    float m_timer;
    CallbackType m_callback;
    int m_repeat;

    virtual void doUpdate(float const /*elapsed*/) override
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
};
} // namespace JamTemplate
#endif
