#include "tween_scale.hpp"
#include <linterp.hpp>

jt::Tween::Sptr jt::TweenScale::create(std::weak_ptr<jt::DrawableInterface> obj, float time,
    jt::Vector2f valueStart, jt::Vector2f valueEnd)
{
    return std::make_shared<TweenScale>(obj, time, valueStart, valueEnd);
}

jt::TweenScale::TweenScale(std::weak_ptr<jt::DrawableInterface> obj, float time,
    jt::Vector2f valueStart, jt::Vector2f valueEnd)
    : Tween { obj, time }
    , m_initialValue { valueStart }
    , m_finalValue { valueEnd }
{
}

void jt::TweenScale::doUpdateObject(
    std::shared_ptr<jt::DrawableInterface> const& sptr, float agePercent) const
{
    auto scale = sptr->getScale();

    scale.x = std::lerp(
        static_cast<float>(m_initialValue.x), static_cast<float>(m_finalValue.x), agePercent);
    scale.y = std::lerp(
        static_cast<float>(m_initialValue.y), static_cast<float>(m_finalValue.y), agePercent);

    sptr->setScale(scale);
}
