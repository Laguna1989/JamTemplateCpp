#include "StateBox2d.hpp"
#include "../JamTemplate/InputManager.hpp"
#include "State1.hpp"

void StateBox2d::doInternalUpdate(float const elapsed)
{
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int32 i = 0; i < 60; ++i) {
        m_world->Step(elapsed, velocityIterations, positionIterations);
    }

    if (getAge() >= 15.0f || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1)) {
        getGame()->switchState(std::make_shared<State1>());
    }

    float max_T = 5.5f;
    float current = getAge() / max_T;
    while (current > 1) {
        current = current - 1.0f;
    }
    if (current < 0) {
        current = 0;
    }
    float v = JamTemplate::Lerp::cosine(0.0f, 1.0f, current);
    m_bar1->setCurrentValue(v);
    if (current < 0.25f) {
        m_bar1->setFrontColor(sf::Color::Red);
    } else {
        m_bar1->setFrontColor(sf::Color::White);
    }

    m_bar2->setCurrentValue((1 - v));
    m_bar2->setBackColor(sf::Color::Blue);
}
