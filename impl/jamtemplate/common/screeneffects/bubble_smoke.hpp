#ifndef JAMTEMPLATE_BUBBLE_SMOKE_HPP
#define JAMTEMPLATE_BUBBLE_SMOKE_HPP

#include "ease/ease_from_points.hpp"
#include <game_object.hpp>
#include <particle_system.hpp>
#include <shape.hpp>
#include <tween_collection.hpp>
#include <tweens/tween_base.hpp>

namespace jt {
/// A smoke screen effect
class BubbleSmoke : public jt::GameObject {
public:
    /// Fire the bubble smoke at a given position
    /// \param pos position to fire at
    void fire(jt::Vector2f const& pos);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    void addTween(std::shared_ptr<jt::TweenInterface> tween);

    std::shared_ptr<jt::ParticleSystem<jt::Shape, 100>> m_particles { nullptr };
    jt::TweenCollection m_tweens;

    float m_fireTimer { 0.0f };

    jt::Vector2f m_smokePos { 0.0f, 0.0f };
};

} // namespace jt

#endif // JAMTEMPLATE_BUBBLE_SMOKE_HPP
