#include "tween_alpha.hpp"
#include <linterp.hpp>

jt::Tween::Sptr jt::TweenAlpha::create(std::weak_ptr<jt::DrawableInterface> obj,
    float tweenDurationInSeconds, std::uint8_t valueStart, std::uint8_t valueEnd)
{
    return std::make_shared<TweenAlpha>(obj, tweenDurationInSeconds, valueStart, valueEnd);
}

jt::TweenAlpha::TweenAlpha(std::weak_ptr<jt::DrawableInterface> obj, float tweenDurationInSeconds,
    std::uint8_t valueStart, std::uint8_t valueEnd)
    : Tween { obj, tweenDurationInSeconds }
    , m_initialValue { static_cast<float>(valueStart) / 255.0f }
    , m_finalValue { static_cast<float>(valueEnd) / 255.0f }
{
}

void jt::TweenAlpha::doUpdateObject(
    std::shared_ptr<jt::DrawableInterface> const& sptr, float agePercent) const
{
    jt::Color col = sptr->getColor();
    float const alpha = Lerp::linear(m_initialValue, m_finalValue, agePercent);
    col.a = static_cast<std::uint8_t>(alpha * 255.0f);
    sptr->setColor(col);
}
