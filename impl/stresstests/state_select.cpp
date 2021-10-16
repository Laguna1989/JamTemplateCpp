#include "state_select.hpp"
#include "state_box2d.hpp"
#include "state_explosion.hpp"
#include "state_particles.h"
#include "state_rope.hpp"
#include "state_scroll.hpp"
#include "state_swarmobjects.hpp"
#include "state_tileson.hpp"
#include "state_tween.hpp"

void StateSelect::doInternalCreate()
{
    AddButton<StateExplosion>("Explode");
    AddButton<StateSwarmObjects>("Swarm");
    AddButton<StateTween>("Tweens");
    AddButton<StateTileson>("Tilemap");
    AddButton<StateBox2d>("Box2D");
    AddButton<StateScroll>("Move Cam");
    AddButton<StateRope>("Rope");
    AddButton<StateParticles>("Particles");
}

void StateSelect::doInternalUpdate(float /*elapsed*/)
{
    // nothing to do here
}

void StateSelect::doInternalDraw() const
{
    // nothing to do here
}
