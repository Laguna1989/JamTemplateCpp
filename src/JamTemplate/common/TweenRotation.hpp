﻿#ifndef GUARD_JAMTEMPLATE_TWEENROTATION_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENROTATION_HPP_INCLUDEGUARD

#include "Lerp.hpp"
#include "TweenBase.hpp"

namespace jt {

template <class T>
class TweenRotation : public Tween<T> {
public:
    // Tween rotation from valueStart to valueEnd of obj withtin time
    static TweenBase::Sptr create(
        std::weak_ptr<T> obj, float time, float valueStart, float valueEnd)
    {
        return std::make_shared<TweenRotation>(obj, time, valueStart, valueEnd);
    }

    // Tween position from valueStart to valueEnd of obj withtin time
    TweenRotation(std::weak_ptr<T> obj, float time, float valueStart, float valueEnd)
        : Tween<T> { obj,
            [this](auto sptr, auto agePercent) {
                float rot = Lerp::linear(static_cast<float>(m_initialValue),
                    static_cast<float>(m_finalValue), agePercent);

                sptr->setRotation(rot);
                return (agePercent < 1.0f);
            },
            time }
    {
        m_initialValue = valueStart;
        m_finalValue = valueEnd;
    }

private:
    float m_initialValue { 0.0f };
    float m_finalValue { 0.0f };
};
} // namespace jt

#endif
