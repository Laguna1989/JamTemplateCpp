#include "State1.hpp"
#include "InputManager.hpp"
#include "State2.hpp"
#include "Timer.hpp"
#include "TweenAlpha.hpp"
#include "TweenColor.hpp"
#include "TweenScale.hpp"

void State1::doInternalUpdate(float const /*elapsed*/)
{
    unsigned int N = 1;
    for (unsigned int i = 0; i != N; ++i) {
        Object::Sptr bp = std::make_shared<Object>();
        add(bp);
        using JamTemplate::Timer;
        Timer::Sptr t = std::make_shared<Timer>(
            JamTemplate::Random::getFloat(0.125, 3), [bp]() { bp->Flash(); });
        add(t);

        auto tw = JamTemplate::TweenAlpha<JamTemplate::SmartAnimation>::create(
            bp->getAnimation(), 0.1f, 255, 0);
        tw->setStartDelay(0.75f);
        add(tw);

        auto tw2 = JamTemplate::TweenColor<JamTemplate::SmartAnimation>::create(
            bp->getAnimation(), 0.4f, sf::Color::White, sf::Color::Red);
        tw2->setStartDelay(0.4f);
        add(tw2);

        auto tw3 = JamTemplate::TweenScale<JamTemplate::SmartAnimation>::create(
            bp->getAnimation(), 0.9f, sf::Vector2f { 1, 1 }, sf::Vector2f { 3, 3 });
        add(tw3);
    }

    if (getAge() >= 5.0 || JamTemplate::InputManager::justPressed(sf::Keyboard::F1)) {
        getGame()->switchState(std::make_shared<State2>());
    }
}
