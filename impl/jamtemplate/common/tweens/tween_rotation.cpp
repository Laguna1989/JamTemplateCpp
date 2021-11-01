#include "tween_rotation.hpp"
#include "linterp.hpp"

namespace jt {

Tween::Sptr TweenRotation::create(
    std::weak_ptr<DrawableInterface> obj, float time, float valueStart, float valueEnd)
{
    return std::make_shared<TweenRotation>(obj, time, valueStart, valueEnd);
}

TweenRotation::TweenRotation(
    std::weak_ptr<DrawableInterface> obj, float time, float valueStart, float valueEnd)
    : Tween { obj, time }
    , m_initialValue { valueStart }
    , m_finalValue { valueEnd }
{
}

void TweenRotation::doUpdateObject(
    std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const
{
    float const rot = Lerp::linear(
        static_cast<float>(m_initialValue), static_cast<float>(m_finalValue), agePercent);
    sptr->setRotation(rot);
}
} // namespace jt
