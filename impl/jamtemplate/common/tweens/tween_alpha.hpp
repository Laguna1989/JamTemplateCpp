#ifndef GUARD_JAMTEMPLATE_TWEENALPHA_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENALPHA_HPP_INCLUDEGUARD

#include "tween_base.hpp"
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
