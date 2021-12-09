#ifndef GUARD_JAMTEMPLATE_TWEENPOSITION_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENPOSITION_HPP_INCLUDEGUARD

#include "tween_base.hpp"
#include "vector.hpp"

namespace jt {

/// Tween position of obj from valueStart to valueEnd
class TweenPosition : public Tween {
public:
    static Tween::Sptr create(std::weak_ptr<DrawableInterface> obj, float time,
        jt::Vector2f valueStart, jt::Vector2f valueEnd);

    TweenPosition(std::weak_ptr<DrawableInterface> obj, float time, jt::Vector2f valueStart,
        jt::Vector2f valueEnd);

private:
    jt::Vector2f m_initialValue { 0.0f, 0.0f };
    jt::Vector2f m_finalValue { 0.0f, 0.0f };

    void doUpdateObject(
        std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const override;
};

} // namespace jt

#endif
