#include "tween_color.hpp"
#include "linterp.hpp"

namespace jt {

Tween::Sptr TweenColor::create(
    std::weak_ptr<DrawableInterface> obj, float time, jt::Color valueStart, jt::Color valueEnd)
{
    return std::make_shared<TweenColor>(obj, time, valueStart, valueEnd);
}

TweenColor::TweenColor(
    std::weak_ptr<DrawableInterface> obj, float time, jt::Color valueStart, jt::Color valueEnd)
    : Tween { obj, time }
    , m_initialValue { valueStart }
    , m_finalValue { valueEnd }
{
}

void TweenColor::doUpdateObject(
    std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const
{
    auto col = sptr->getColor();

    float const r = Lerp::linear(
        static_cast<float>(m_initialValue.r), static_cast<float>(m_finalValue.r), agePercent);
    float const g = Lerp::linear(
        static_cast<float>(m_initialValue.g), static_cast<float>(m_finalValue.g), agePercent);
    float const b = Lerp::linear(
        static_cast<float>(m_initialValue.b), static_cast<float>(m_finalValue.b), agePercent);

    col.r = static_cast<std::uint8_t>(r);
    col.g = static_cast<std::uint8_t>(g);
    col.b = static_cast<std::uint8_t>(b);
    sptr->setColor(col);
}
} // namespace jt
