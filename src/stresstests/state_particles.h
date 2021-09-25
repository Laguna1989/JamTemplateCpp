
#ifndef MYAWESOMEGAME_STATE_PARTICLES_H
#define MYAWESOMEGAME_STATE_PARTICLES_H

#include "circular_buffer.hpp"
#include "game_state.hpp"
#include "particle_system.hpp"
#include "shape.hpp"
#include <memory>

constexpr std::size_t numberOfParticles = 5000;
constexpr std::size_t toFire = 20;

class StateParticles : public jt::GameState {
private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
    std::shared_ptr<jt::ParticleSystem<jt::Shape, numberOfParticles>> m_particles;
    jt::CircularBuffer<float, 200> m_timeMeasurement;
};

#endif // MYAWESOMEGAME_STATE_PARTICLES_H
