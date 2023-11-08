#ifndef JAMTEMAPLTE_PARTICLE_SYSTEM_DROP_ITEMS
#define JAMTEMAPLTE_PARTICLE_SYSTEM_DROP_ITEMS

#include <animation.hpp>
#include <game_object.hpp>
#include <particle_system.hpp>
#include <tween_collection.hpp>

// TODO add to demo
class ParticleSystemDropItems : public jt::GameObject {
public:
    ParticleSystemDropItems(std::string const& aseFileName, float radius);
    void fire(int number, jt::Vector2f const& pos);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::string m_aseFileName {};
    float m_radius { 0.0f };

    std::shared_ptr<jt::ParticleSystem<jt::Animation, 12>> m_particles { nullptr };
    std::shared_ptr<jt::TweenCollection> m_tweens { nullptr };
};

#endif // JAMTEMAPLTE_PARTICLE_SYSTEM_DROP_ITEMS
