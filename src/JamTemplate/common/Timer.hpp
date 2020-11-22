#ifndef JAMTEMPLATE_TIMER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TIMER_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include <functional>

namespace JamTemplate {

// forward declaration
class Game;

class Timer : public GameObject {
public:
    using CallbackType = std::function<void(void)>;
    Timer(float t, CallbackType cb, int r = -1);

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

    virtual void doUpdate(float const /*elapsed*/) override;
};
} // namespace JamTemplate
#endif
