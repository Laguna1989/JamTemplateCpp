#ifndef GUARD_JAMTEMPLATE_RANDOM_SAMPLEANDHOLD_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_RANDOM_SAMPLEANDHOLD_HPP_INCLUDEGUARD

namespace jt {

class SampleAndHold {
public:
    SampleAndHold(float timerMu, float timerSigma);
    void update(float elapsed);
    float getFloat() const;

private:
    float m_timerMu { 0.0f };
    float m_timerSigma { 0.0f };
    float m_timer { 0.0f };
    float m_value { 0.0f };

    void sampleNewValue();
};

} // namespace jt
#endif
