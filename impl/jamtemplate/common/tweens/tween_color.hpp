#ifndef GUARD_JAMTEMPLATE_TWEENCOLOR_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENCOLOR_HPP_INCLUDEGUARD

#include "color.hpp"
#include "tween_base.hpp"

namespace jt {

/// Tween color of obj from valueStart to valueEnd, ignoring the alpha value
class TweenColor : public Tween {
public:
    static Tween::Sptr create(
        std::weak_ptr<DrawableInterface> obj, float time, jt::Color valueStart, jt::Color valueEnd);

    TweenColor(
        std::weak_ptr<DrawableInterface> obj, float time, jt::Color valueStart, jt::Color valueEnd);

private:
    jt::Color m_initialValue;
    jt::Color m_finalValue;

    void doUpdateObject(
        std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const override;
};

} // namespace jt

#endif
