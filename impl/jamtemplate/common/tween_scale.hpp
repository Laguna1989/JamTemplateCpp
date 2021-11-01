#ifndef GUARD_JAMTEMPLATE_TWEENSCALE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENSCALE_HPP_INCLUDEGUARD

#include "linterp.hpp"
#include "tween_base.hpp"
#include "vector.hpp"

namespace jt {

class TweenScale : public Tween {
public:
    // Tween scale from valueStart to valueEnd of obj within time
    static Tween::Sptr create(std::weak_ptr<DrawableInterface> obj, float time,
        jt::Vector2 valueStart, jt::Vector2 valueEnd)
    {
        return std::make_shared<TweenScale>(obj, time, valueStart, valueEnd);
    }

    // Tween scale from valueStart to valueEnd of obj within time
    TweenScale(std::weak_ptr<DrawableInterface> obj, float time, jt::Vector2 valueStart,
        jt::Vector2 valueEnd)
        : Tween { obj, time }
    {
        m_initialValue = valueStart;
        m_finalValue = valueEnd;
    }

private:
    jt::Vector2 m_initialValue { 0.0f, 0.0f };
    jt::Vector2 m_finalValue { 0.0f, 0.0f };

    void doUpdateObject(
        std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const override
    {
        auto scale = sptr->getScale();

        scale.x() = Lerp::linear(static_cast<float>(m_initialValue.x()),
            static_cast<float>(m_finalValue.x()), agePercent);
        scale.y() = Lerp::linear(static_cast<float>(m_initialValue.y()),
            static_cast<float>(m_finalValue.y()), agePercent);

        sptr->setScale(scale);
    }
};

} // namespace jt

#endif
