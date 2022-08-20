#ifndef JAMTEMPLATE_FLICKER_IMPL_HPP
#define JAMTEMPLATE_FLICKER_IMPL_HPP

namespace jt {

class FlickerImpl {
public:
    void updateFlicker(float elapsed);
    bool allowDrawFromFlicker() const;
    bool doesFlickerAffectsShadow() const;

    void doFlicker(float duration, float interval = 0.1f, bool affectShadow = false);

private:
    float m_flickerTimer { 0.0f };
    float m_flickerInterval { 0.1f };
    float m_flickerIntervalTimer { 0.0f };
    bool m_doDraw { true };

    bool m_affectShadow { false };
};

} // namespace jt

#endif // JAMTEMPLATE_FLICKER_IMPL_HPP
