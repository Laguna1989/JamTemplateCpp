#ifndef JAMTEMPLATE_TWEENCOLOR_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TWEENCOLOR_HPP_INCLUDEGUARD

#include "Lerp.hpp"
#include "TweenBase.hpp"

namespace JamTemplate {
template <class T>
class TweenColor : public Tween<T> {
public:
    // Tween color from valueStart to valueEnd of obj withtin time
    static TweenBase::Sptr create(std::weak_ptr<T> obj, float time, sf::Color valueStart, sf::Color valueEnd)
    {
        return std::make_shared<TweenColor>(obj, time, valueStart, valueEnd);
    }

    // Tween color from valueStart to valueEnd of obj withtin time
    TweenColor(std::weak_ptr<T> obj, float time, sf::Color valueStart, sf::Color valueEnd)
        : Tween<T> { obj, [this](auto sptr, auto age) {
                        auto col = sptr->getColor();

                        float val = age / m_totalTime;

                        float r = Lerp::linear(static_cast<float>(m_initialValue.r), static_cast<float>(m_finalValue.r), val);
                        float g = Lerp::linear(static_cast<float>(m_initialValue.g), static_cast<float>(m_finalValue.g), val);
                        float b = Lerp::linear(static_cast<float>(m_initialValue.b), static_cast<float>(m_finalValue.b), val);

                        col.r = static_cast<sf::Uint8>(r);
                        col.g = static_cast<sf::Uint8>(g);
                        col.b = static_cast<sf::Uint8>(b);
                        sptr->setColor(col);
                        return (age < m_totalTime);
                    } }
    {
        m_totalTime = time;
        m_initialValue = valueStart;
        m_finalValue = valueEnd;
    }

private:
    float m_totalTime { 1.0f };
    sf::Color m_initialValue {};
    sf::Color m_finalValue {};
};
} // namespace JamTemplate

#endif
