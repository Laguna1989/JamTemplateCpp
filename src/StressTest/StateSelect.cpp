#include "StateSelect.hpp"
#include "SmartText.hpp"
#include "State1.hpp"
#include "State2.hpp"
#include "StateBox2d.hpp"
#include "StateTileson.hpp"
#include "StateTween.hpp"

void StateSelect::doInternalCreate()
{
    using namespace detail;
    std::size_t count { 0 };

    AddButton<State1>("State 1");
    AddButton<State2>("State 2");
    AddButton<StateTween>("Tweens");
    AddButton<StateTileson>("Tilemap");
    AddButton<StateBox2d>("Box2D");
}

void StateSelect::doInternalUpdate(float elapsed) { }

void StateSelect::doInternalDraw() const { }
