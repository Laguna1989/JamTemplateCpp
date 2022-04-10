#include "tween_rotation.hpp"
#include <linterp.hpp>

jt::Tween::Sptr jt::TweenRotation::create(
    std::weak_ptr<jt::DrawableInterface> obj, float time, float valueStart, float valueEnd)
{
    return std::make_shared<TweenRotation>(obj, time, valueStart, valueEnd);
}

jt::TweenRotation::TweenRotation(
    std::weak_ptr<jt::DrawableInterface> obj, float time, float valueStart, float valueEnd)
    : Tween { obj, time }
    , m_initialValue { valueStart }
    , m_finalValue { valueEnd }
{
}

void jt::TweenRotation::doUpdateObject(
    std::shared_ptr<jt::DrawableInterface> const& sptr, float agePercent) const
{
    float const rot = Lerp::linear(
        static_cast<float>(m_initialValue), static_cast<float>(m_finalValue), agePercent);
    sptr->setRotation(rot);
}
