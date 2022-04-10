#include "tween_position.hpp"
#include <linterp.hpp>

jt::Tween::Sptr jt::TweenPosition::create(std::weak_ptr<DrawableInterface> obj, float time,
    jt::Vector2f valueStart, jt::Vector2f valueEnd)
{
    return std::make_shared<TweenPosition>(obj, time, valueStart, valueEnd);
}

jt::TweenPosition::TweenPosition(std::weak_ptr<jt::DrawableInterface> obj, float time,
    jt::Vector2f valueStart, jt::Vector2f valueEnd)
    : Tween { obj, time }
    , m_initialValue { valueStart }
    , m_finalValue { valueEnd }
{
}

void jt::TweenPosition::doUpdateObject(
    std::shared_ptr<jt::DrawableInterface> const& sptr, float agePercent) const
{
    auto pos = sptr->getPosition();

    pos.x = Lerp::linear(
        static_cast<float>(m_initialValue.x), static_cast<float>(m_finalValue.x), agePercent);
    pos.y = Lerp::linear(
        static_cast<float>(m_initialValue.y), static_cast<float>(m_finalValue.y), agePercent);

    sptr->setPosition(pos);
}
