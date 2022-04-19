#ifndef JAMTEMPLATE_SHAKE_IMPL_HPP
#define JAMTEMPLATE_SHAKE_IMPL_HPP

#include <vector.hpp>

namespace jt {

class ShakeImpl {
public:
    void updateShake(float elapsed);
    void doShake(float t, float strength, float shakeInterval);
    jt::Vector2f doGetShakeOffset() const;

private:
    float m_shakeTimer { -1.0f };
    float m_shakeTimerMax { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    jt::Vector2f m_shakeOffset { 0, 0 };
};

} // namespace jt

#endif // JAMTEMPLATE_SHAKE_IMPL_HPP
