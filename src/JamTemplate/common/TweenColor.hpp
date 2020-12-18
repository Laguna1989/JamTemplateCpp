#ifndef GUARD_JAMTEMPLATE_TWEENCOLOR_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENCOLOR_HPP_INCLUDEGUARD

#include "Color.hpp"
#include "Lerp.hpp"
#include "TweenBase.hpp"

namespace jt {

template <class T>
class TweenColor : public Tween<T> {
public:
    // Tween color from valueStart to valueEnd of obj withtin time
    static TweenBase::Sptr create(
        std::weak_ptr<T> obj, float time, jt::Color valueStart, jt::Color valueEnd)
    {
        return std::make_shared<TweenColor>(obj, time, valueStart, valueEnd);
    }

    // Tween color from valueStart to valueEnd of obj withtin time
    TweenColor(std::weak_ptr<T> obj, float time, jt::Color valueStart, jt::Color valueEnd)
        : Tween<T> { obj,
            [this](auto sptr, auto agePercent) {
                auto col = sptr->getColor();

                float r = Lerp::linear(static_cast<float>(m_initialValue.r()),
                    static_cast<float>(m_finalValue.r()), agePercent);
                float g = Lerp::linear(static_cast<float>(m_initialValue.g()),
                    static_cast<float>(m_finalValue.g()), agePercent);
                float b = Lerp::linear(static_cast<float>(m_initialValue.b()),
                    static_cast<float>(m_finalValue.b()), agePercent);

                col.r() = static_cast<std::uint8_t>(r);
                col.g() = static_cast<std::uint8_t>(g);
                col.b() = static_cast<std::uint8_t>(b);
                sptr->setColor(col);
                return (agePercent < 1.0f);
            },
            time }
    {
        m_initialValue = valueStart;
        m_finalValue = valueEnd;
    }

private:
    jt::Color m_initialValue {};
    jt::Color m_finalValue {};
};

} // namespace jt

#endif
