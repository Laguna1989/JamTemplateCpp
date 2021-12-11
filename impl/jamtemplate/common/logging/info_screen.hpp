#ifndef GUARD_JAMTEMPLATE_INFO_SCREEN_HPP
#define GUARD_JAMTEMPLATE_INFO_SCREEN_HPP

#include "circular_buffer.hpp"
#include "game_object.hpp"

namespace jt {
class InfoScreen : public ::jt::GameObject {
private:
    mutable bool m_showInfo { false };

    jt::CircularBuffer<float, 200> m_frameTimes;
    std::vector<float> m_frameTimesVector;

    virtual void doCreate();
    virtual void doUpdate(float const /*elapsed*/);
    virtual void doDraw() const;
};
} // namespace jt

#endif // MYAWESOMEGAME_INFO_SCREEN_HPP
