
#ifndef MYAWESOMEGAME_STATE_PARTICLES_H
#define MYAWESOMEGAME_STATE_PARTICLES_H

#include "game_state.hpp"
#include "particle_system.hpp"
#include "shape.hpp"
#include <memory>

class StateParticles : public jt::GameState {
private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
    std::shared_ptr<jt::ParticleSystem<jt::Shape, 500>> m_particles;
};

#endif // MYAWESOMEGAME_STATE_PARTICLES_H
