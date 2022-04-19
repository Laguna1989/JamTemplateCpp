#ifndef JAMTEMPLATE_TWEENROTATION_HPP
#define JAMTEMPLATE_TWEENROTATION_HPP

#include <tweens/tween_base.hpp>

namespace jt {

/// Tween rotation of obj from valueStart to valueEnd
class TweenRotation : public Tween {
public:
    static Tween::Sptr create(
        std::weak_ptr<DrawableInterface> obj, float time, float valueStart, float valueEnd);

    TweenRotation(
        std::weak_ptr<DrawableInterface> obj, float time, float valueStart, float valueEnd);

private:
    float m_initialValue { 0.0f };
    float m_finalValue { 0.0f };

    void doUpdateObject(
        std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const override;
};
} // namespace jt

#endif
