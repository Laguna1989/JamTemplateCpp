#include "random_sample_and_hold.hpp"
#include <random/random.hpp>

jt::SampleAndHold::SampleAndHold(float timerMu, float timerSigma)
{
    m_timerMu = timerMu;
    m_timerSigma = timerSigma;
    sampleNewValue();
}

void jt::SampleAndHold::update(float elapsed)
{
    m_timer -= elapsed;
    if (m_timer <= 0) {
        sampleNewValue();
    }
}

float jt::SampleAndHold::getFloat() const { return m_value; }

void jt::SampleAndHold::sampleNewValue()
{
    m_value = jt::Random::getFloat(0.0f, 1.0f);
    m_timer = jt::Random::getFloatGauss(m_timerMu, m_timerSigma);
}
