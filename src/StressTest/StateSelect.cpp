#include "StateSelect.hpp"
#include "Button.hpp"
#include "SmartText.hpp"
#include "State1.hpp"

void StateSelect::doInternalCreate()
{
    auto const b1 = std::make_shared<jt::Button>();
    b1->addCallback([this]() { getGame()->switchState(std::make_shared<State1>()); });
    auto const t1 = std::make_shared<jt::SmartText>();
    t1->loadFont("assets/font.ttf", 8, getGame()->getRenderTarget());
    t1->setText("State 1");
    b1->setDrawable(t1);
    add(b1);
}

void StateSelect::doInternalUpdate(float elapsed) { }

void StateSelect::doInternalDraw() const { }
