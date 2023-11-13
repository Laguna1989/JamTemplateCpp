#ifndef JAMTEMPLATE_TRAILING_CIRCLES_HPP
#define JAMTEMPLATE_TRAILING_CIRCLES_HPP

#include <animation.hpp>
#include <game_object.hpp>
#include <particle_system.hpp>
#include <tween_collection.hpp>

namespace jt {

/// A trailing circles screen effect
class TrailingCircles : public jt::GameObject {
public:
    /// setPosition for TrailingCircles
    /// \param pos Position of the TrailingCircles
    void setPosition(jt::Vector2f const& pos);

    /// set max timer how often a trailing circle is created
    /// \param max timer in seconds
    void setTimerMax(float max);

    /// set the max alpha value of the trailing circles
    /// \param maxAlpha  alpha value 0-255
    void setMaxAlpha(std::uint8_t maxAlpha);

    /// set the z layer of the trailing circles
    /// \param zLayer z layer
    void setZ(int zLayer);

    /// set the effect enabled or disabled
    void setEnabled(bool enable);

    /// set the max distance to spawn a circle
    void setMaxDistanceToSpawnCircle(float maxDistance);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    using ParticleSystemType = jt::ParticleSystem<jt::Animation, 20u>;

    std::shared_ptr<ParticleSystemType> m_particles;
    std::shared_ptr<jt::TweenCollection> m_tweens;

    jt::Vector2f m_pos;
    float m_timer { 0.0f };
    float m_timerMax { 0.2 };
    std::uint8_t m_maxAlpha { 255u };

    bool m_enabled { true };
    float m_maxDistance { -1.0f };
    float m_summedUpDistance { 0.0f };
};
} // namespace jt

#endif // JAMTEMPLATE_TRAILING_CIRCLES_HPP
