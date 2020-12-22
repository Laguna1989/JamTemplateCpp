#ifndef GUARD_JAMTEMPLATE_TWEENALPHA_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENALPHA_HPP_INCLUDEGUARD

#include "Color.hpp"
#include "Lerp.hpp"
#include "TweenBase.hpp"
#include <cstdint>

namespace jt {

template <class T>
class TweenAlpha : public Tween<T> {
public:
    // Tween alpha value from valueStart to valueEnd of obj withtin time
    static TweenBase::Sptr create(
        std::weak_ptr<T> obj, float time, std::uint8_t valueStart, std::uint8_t valueEnd)
    {
        return std::make_shared<TweenAlpha>(obj, time, valueStart, valueEnd);
    }

    // Tween alpha value from valueStart to valueEnd of obj withtin time
    TweenAlpha(std::weak_ptr<T> obj, float time, std::uint8_t valueStart, std::uint8_t valueEnd)
        : Tween<T> { obj,
            [this](auto sptr, auto agePercent) {
                jt::Color col = sptr->getColor();
                float alpha = Lerp::linear(m_initialValue, m_finalValue, agePercent);
                std::uint8_t a = static_cast<std::uint8_t>(alpha * 255.0f);
                col.a() = a;
                sptr->setColor(col);

                return (agePercent < 1.0f);
            },
            time }
    {
        m_initialValue = static_cast<float>(valueStart) / 255.0f;
        m_finalValue = static_cast<float>(valueEnd) / 255.0f;
    }

private:
    float m_initialValue { 0.0f };
    float m_finalValue { 0.0f };
};

} // namespace jt

#endif
