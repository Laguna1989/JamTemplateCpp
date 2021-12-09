#include "tween_scale.hpp"
#include "linterp.hpp"

namespace jt {

Tween::Sptr TweenScale::create(std::weak_ptr<DrawableInterface> obj, float time,
    jt::Vector2f valueStart, jt::Vector2f valueEnd)
{
    return std::make_shared<TweenScale>(obj, time, valueStart, valueEnd);
}

TweenScale::TweenScale(std::weak_ptr<DrawableInterface> obj, float time, jt::Vector2f valueStart,
    jt::Vector2f valueEnd)
    : Tween { obj, time }
    , m_initialValue { valueStart }
    , m_finalValue { valueEnd }
{
}

void TweenScale::doUpdateObject(
    std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const
{
    auto scale = sptr->getScale();

    scale.x = Lerp::linear(
        static_cast<float>(m_initialValue.x), static_cast<float>(m_finalValue.x), agePercent);
    scale.y = Lerp::linear(
        static_cast<float>(m_initialValue.y), static_cast<float>(m_finalValue.y), agePercent);

    sptr->setScale(scale);
}
} // namespace jt
