#ifndef JAMTEMPLATE_TWEENALPHA_HPP
#define JAMTEMPLATE_TWEENALPHA_HPP

#include <tweens/tween_base.hpp>
#include <cstdint>

namespace jt {

/// Tween alpha value from valueStart to valueEnd of obj within time
class TweenAlpha : public Tween {
public:
    static Tween::Sptr create(std::weak_ptr<DrawableInterface> obj, float tweenDurationInSeconds,
        std::uint8_t valueStart, std::uint8_t valueEnd);

    TweenAlpha(std::weak_ptr<DrawableInterface> obj, float tweenDurationInSeconds,
        std::uint8_t valueStart, std::uint8_t valueEnd);

private:
    float m_initialValue;
    float m_finalValue;

    void doUpdateObject(
        std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const override;
};

} // namespace jt

#endif
