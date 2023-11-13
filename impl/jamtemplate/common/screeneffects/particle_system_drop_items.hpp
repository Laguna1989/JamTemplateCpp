#ifndef JAMTEMAPLTE_PARTICLE_SYSTEM_DROP_ITEMS
#define JAMTEMAPLTE_PARTICLE_SYSTEM_DROP_ITEMS

#include <animation.hpp>
#include <game_object.hpp>
#include <particle_system.hpp>
#include <tween_collection.hpp>

namespace jt {

/// A screen effect that drops items
class ParticleSystemDropItems : public jt::GameObject {
public:
    /// Constructor
    /// \param aseFileName filename of the aseprite file. Particles will randomly pick one animation
    /// \param radius radius of the circle to where the particles will move
    /// \param time time in seconds until items disappear
    ParticleSystemDropItems(std::string const& aseFileName, float radius, float time);

    /// Fire the particles at a given position
    /// \param number number of particles to fire
    /// \param pos position to fire at
    void fire(int number, jt::Vector2f const& pos);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::string m_aseFileName {};
    float m_radius { 0.0f };
    float m_time { 1.0f };

    std::shared_ptr<jt::ParticleSystem<jt::Animation, 12u>> m_particles { nullptr };
    std::shared_ptr<jt::TweenCollection> m_tweens { nullptr };
};

} // namespace jt

#endif // JAMTEMAPLTE_PARTICLE_SYSTEM_DROP_ITEMS
