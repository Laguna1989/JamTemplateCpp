#ifndef GUARD_JAMTEMPLATE_TWEENSCALE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENSCALE_HPP_INCLUDEGUARD

#include "Lerp.hpp"
#include "TweenBase.hpp"
#include "Vector.hpp"

namespace jt {

template <class T>
class TweenScale : public Tween<T> {
public:
    // Tween scale from valueStart to valueEnd of obj withtin time
    static TweenBase::Sptr create(
        std::weak_ptr<T> obj, float time, jt::Vector2 valueStart, jt::Vector2 valueEnd)
    {
        return std::make_shared<TweenScale>(obj, time, valueStart, valueEnd);
    }

    // Tween scale from valueStart to valueEnd of obj withtin time
    TweenScale(std::weak_ptr<T> obj, float time, jt::Vector2 valueStart, jt::Vector2 valueEnd)
        : Tween<T> { obj,
            [this](auto sptr, auto agePercent) {
                auto scale = sptr->getScale();

                scale.x() = Lerp::linear(static_cast<float>(m_initialValue.x()),
                    static_cast<float>(m_finalValue.x()), agePercent);
                scale.y() = Lerp::linear(static_cast<float>(m_initialValue.y()),
                    static_cast<float>(m_finalValue.y()), agePercent);

                sptr->setScale(scale);
                return (agePercent < 1.0f);
            },
            time }
    {
        m_initialValue = valueStart;
        m_finalValue = valueEnd;
    }

private:
    jt::Vector2 m_initialValue {};
    jt::Vector2 m_finalValue {};
};

} // namespace jt

#endif
