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

    jt::CircularBuffer<float, 256u> m_frameTimes;
    std::vector<float> m_frameTimesVector;

    mutable std::uint16_t m_numberOfUpdatesInThisFrame { 0 };
    mutable jt::CircularBuffer<float, 256u> m_numberOfUpdatesInLastFrame;

    jt::CircularBuffer<float, 1024u> m_GameObjectAliveCount;
    std::vector<float> m_GameObjectAliveCountVector;

    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
};
} // namespace jt

#endif // JAMTEMPLATE_INFO_SCREEN_HPP
