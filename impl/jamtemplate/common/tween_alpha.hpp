#ifndef GUARD_JAMTEMPLATE_TWEENALPHA_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENALPHA_HPP_INCLUDEGUARD

#include "color.hpp"
#include "linterp.hpp"
#include "tween_base.hpp"
#include <cstdint>

namespace jt {

class TweenAlpha : public Tween {
public:
    // Tween alpha value from valueStart to valueEnd of obj within time
    static Tween::Sptr create(std::weak_ptr<DrawableInterface> obj, float time,
        std::uint8_t valueStart, std::uint8_t valueEnd)
    {
        return std::make_shared<TweenAlpha>(obj, time, valueStart, valueEnd);
    }

public:
    // Tween alpha value from valueStart to valueEnd of obj within tweenDurationInSeconds
    TweenAlpha(std::weak_ptr<DrawableInterface> obj, float tweenDurationInSeconds,
        std::uint8_t valueStart, std::uint8_t valueEnd)
        : Tween { obj, tweenDurationInSeconds }
    {
        m_initialValue = static_cast<float>(valueStart) / 255.0f;
        m_finalValue = static_cast<float>(valueEnd) / 255.0f;
    }

private:
    float m_initialValue { 0.0f };
    float m_finalValue { 0.0f };

    void doUpdateObject(
        std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const override
    {
        jt::Color col = sptr->getColor();
        float const alpha = Lerp::linear(m_initialValue, m_finalValue, agePercent);
        col.a() = static_cast<std::uint8_t>(alpha * 255.0f);
        sptr->setColor(col);
    }
};

} // namespace jt

#endif
