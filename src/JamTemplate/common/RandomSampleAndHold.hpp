#ifndef GUARD_JAMTEMPLATE_RANDOM_SAMPLEANDHOLD_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_RANDOM_SAMPLEANDHOLD_HPP_INCLUDEGUARD

#include "Random.hpp"
namespace jt {

class SampleAndHold {
public:
    SampleAndHold(float timerMu, float timerSigma);
    void update(float elapsed);
    float getFloat() const;

private:
    float m_timerMu;
    float m_timerSigma;
    float m_timer;
    float m_value;

    void sampleNewValue();
};

} // namespace jt
#endif
