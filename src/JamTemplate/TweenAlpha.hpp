#ifndef JAMTEMPLATE_TWEENALPHA_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TWEENALPHA_HPP_INCLUDEGUARD

#include "Lerp.hpp"
#include "TweenBase.hpp"

namespace JamTemplate {
template <class T>
class TweenAlpha : public Tween<T> {
public:
    // Tween alpha value from valueStart to valueEnd of obj withtin time
    static TweenBase::Sptr create(std::weak_ptr<T> obj, float time, sf::Uint8 valueStart, sf::Uint8 valueEnd)
    {
        return std::make_shared<TweenAlpha>(obj, time, valueStart, valueEnd);
    }

    // Tween alpha value from valueStart to valueEnd of obj withtin time
    TweenAlpha(std::weak_ptr<T> obj, float time, sf::Uint8 valueStart, sf::Uint8 valueEnd)
        : Tween<T> { obj, [this](auto sptr, auto age) {
                        auto col = sptr->getColor();
                        float alpha = Lerp::linear(m_initialValue, m_finalValue, age / m_totalTime);
                        sf::Uint8 a = static_cast<sf::Uint8>(alpha * 255.0f);
                        col.a = a;
                        sptr->setColor(col);

                        return (age < m_totalTime);
                    } }
    {
        m_totalTime = time;
        m_initialValue = static_cast<float>(valueStart) / 255.0f;
        m_finalValue = static_cast<float>(valueEnd) / 255.0f;
    }

private:
    float m_totalTime { 1.0f };
    float m_initialValue { 0.0f };
    float m_finalValue { 0.0f };
};
} // namespace JamTemplate

#endif
