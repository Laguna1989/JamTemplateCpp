#include "StateSelect.hpp"
#include "SmartText.hpp"
#include "State1.hpp"
#include "State2.hpp"
#include "StateBox2d.hpp"
#include "StateTileson.hpp"
#include "StateTween.hpp"

void StateSelect::doInternalCreate()
{
    AddButton<State1>("Explode");
    AddButton<State2>("State 2");
    AddButton<StateTween>("Tweens");
    AddButton<StateTileson>("Tilemap");
    AddButton<StateBox2d>("Box2D");
}

void StateSelect::doInternalUpdate(float /*elapsed*/)
{
    // nothing to do here
}

void StateSelect::doInternalDraw() const
{
    // nothing to do here
}
