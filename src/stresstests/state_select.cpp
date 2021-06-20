#include "state_select.hpp"
#include "state1.hpp"
#include "state2.hpp"
#include "state_box2d.hpp"
#include "state_scroll.hpp"
#include "state_tileson.hpp"
#include "state_tween.hpp"

void StateSelect::doInternalCreate()
{
    AddButton<State1>("Explode");
    AddButton<State2>("State 2");
    AddButton<StateTween>("Tweens");
    AddButton<StateTileson>("Tilemap");
    AddButton<StateBox2d>("Box2D");
    AddButton<StateScroll>("Move Cam");
}

void StateSelect::doInternalUpdate(float /*elapsed*/)
{
    // nothing to do here
}

void StateSelect::doInternalDraw() const
{
    // nothing to do here
}
