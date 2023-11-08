#ifndef JAMTEMPLATE_TRAILING_CIRCLES_HPP
#define JAMTEMPLATE_TRAILING_CIRCLES_HPP

#include <animation.hpp>
#include <game_object.hpp>
#include <particle_system.hpp>
#include <tween_collection.hpp>

namespace jt {

// TODO comment
// TODO add to demo
class TrailingCircles : public jt::GameObject {
public:
    void setPosition(jt::Vector2f const& pos);
    void setTimerMax(float max);
    void setMaxAlpha(std::uint8_t maxAlpha);

    void setZ(int zLayer);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    using ParticleSystemType = jt::ParticleSystem<jt::Animation, 20>;

    std::shared_ptr<ParticleSystemType> m_particles;
    std::shared_ptr<jt::TweenCollection> m_tweens;

    jt::Vector2f m_pos;
    float m_timer { 0.0f };
    float m_timerMax { 0.2 };
    std::uint8_t m_maxAlpha { 255u };
};
} // namespace jt

#endif // JAMTEMPLATE_TRAILING_CIRCLES_HPP
