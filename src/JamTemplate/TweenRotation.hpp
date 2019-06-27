#ifndef JAMTEMPLATE_TWEENROTATION_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TWEENROTATION_HPP_INCLUDEGUARD

#include "Lerp.hpp"
#include "TweenBase.hpp"

namespace JamTemplate {
template <class T>
class TweenRotation : public Tween<T> {
public:
    // Tween rotation from valueStart to valueEnd of obj withtin time
    static TweenBase::Sptr create(std::weak_ptr<T> obj, float time, float valueStart, float valueEnd)
    {
        return std::make_shared<TweenRotation>(obj, time, valueStart, valueEnd);
    }

    // Tween position from valueStart to valueEnd of obj withtin time
    TweenRotation(std::weak_ptr<T> obj, float time, float valueStart, float valueEnd)
        : Tween<T> { obj, [this](auto sptr, auto age) {
                        float val = age / m_totalTime;

                        float rot = Lerp::linear(static_cast<float>(m_initialValue), static_cast<float>(m_finalValue), val);

                        sptr->setRotation(rot);
                        return true;
                    } }
    {
        m_totalTime = time;
        m_initialValue = valueStart;
        m_finalValue = valueEnd;
    }

private:
    float m_totalTime { 1.0f };
    float m_initialValue { 0.0f };
    float m_finalValue { 0.0f };
};
} // namespace JamTemplate

#endif
