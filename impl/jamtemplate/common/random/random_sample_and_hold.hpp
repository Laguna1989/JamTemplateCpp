#ifndef GUARD_JAMTEMPLATE_RANDOM_SAMPLEANDHOLD_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_RANDOM_SAMPLEANDHOLD_HPP_INCLUDEGUARD

namespace jt {

/// Random sample and hold
class SampleAndHold {
public:
    /// Constructor
    /// \param timerMu timer mu
    /// \param timerSigma timer sigma
    SampleAndHold(float timerMu, float timerSigma);

    /// Update the sample and hold
    /// \param elapsed elapsed time in seconds
    void update(float elapsed);

    /// Get the current random value
    /// \return the random value
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
