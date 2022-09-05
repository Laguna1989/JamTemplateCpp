#ifndef JAMTEMPLATE_TWEENCOLOR_HPP
#define JAMTEMPLATE_TWEENCOLOR_HPP

#include <color/color.hpp>
#include <tweens/tween_base.hpp>

namespace jt {

/// Tween color of obj from valueStart to valueEnd, ignoring the alpha value
class TweenColor : public Tween {
public:
    static Tween::Sptr create(std::weak_ptr<DrawableInterface> obj, float time,
        jt::Color const& valueStart, jt::Color const& valueEnd);

    TweenColor(std::weak_ptr<DrawableInterface> obj, float time, jt::Color const& valueStart,
        jt::Color const& valueEnd);

private:
    jt::Color m_initialValue;
    jt::Color m_finalValue;

    void doUpdateObject(
        std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const override;
};

} // namespace jt

#endif
