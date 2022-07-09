#ifndef JAMTEMPLATE_INFO_SCREEN_HPP
#define JAMTEMPLATE_INFO_SCREEN_HPP

#include <circular_buffer.hpp>
#include <game_object.hpp>

namespace jt {
class InfoScreen : public ::jt::GameObject {
public:
    InfoScreen();

private:
    mutable bool m_showInfo { false };

    jt::CircularBuffer<float, 200> m_frameTimes;
    std::vector<float> m_frameTimesVector;

    jt::CircularBuffer<float, 800> m_GameObjectAliveCount;
    std::vector<float> m_GameObjectAliveCountVector;

    virtual void doCreate();
    virtual void doUpdate(float const /*elapsed*/);
    virtual void doDraw() const;
};
} // namespace jt

#endif // JAMTEMPLATE_INFO_SCREEN_HPP
