#ifndef GUARD_JAMTEMPLATE_TWEENSCALE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENSCALE_HPP_INCLUDEGUARD

#include "tween_base.hpp"
#include "vector.hpp"

namespace jt {

/// Tween scale of obj from valueStart to valueEnd
class TweenScale : public Tween {
public:
    static Tween::Sptr create(std::weak_ptr<DrawableInterface> obj, float time,
        jt::Vector2f valueStart, jt::Vector2f valueEnd);

    TweenScale(std::weak_ptr<DrawableInterface> obj, float time, jt::Vector2f valueStart,
        jt::Vector2f valueEnd);

private:
    jt::Vector2f m_initialValue;
    jt::Vector2f m_finalValue;

    void doUpdateObject(
        std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const override;
};

} // namespace jt

#endif
