
#ifndef JAMTEMPLATE_STATE_PARTICLES_H
#define JAMTEMPLATE_STATE_PARTICLES_H

#include <animation.hpp>
#include <circular_buffer.hpp>
#include <game_state.hpp>
#include <particle_system.hpp>
#include <shape.hpp>
#include <memory>

constexpr std::size_t numberOfParticles = 500;
constexpr std::size_t toFire = 20;

class StateParticles : public jt::GameState {
public:
    std::string getName() const override;

private:
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;
    std::shared_ptr<jt::ParticleSystem<jt::Shape, numberOfParticles>> m_particlesGlitter;
    std::shared_ptr<jt::ParticleSystem<jt::Shape, numberOfParticles>> m_particlesFire;
    std::shared_ptr<jt::ParticleSystem<jt::Animation, 100>> m_sparkParticles;

    jt::CircularBuffer<float, 200> m_timeMeasurement;
    void createParticlesGlitter();
    void createParticlesFire();
    void createSparkParticles();
};

#endif // JAMTEMPLATE_STATE_PARTICLES_H
