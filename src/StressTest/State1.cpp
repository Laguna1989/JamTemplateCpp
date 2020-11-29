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
        using jt::Timer;
        Timer::Sptr t
            = std::make_shared<Timer>(jt::Random::getFloat(0.125, 3), [bp]() { bp->Flash(); });
        add(t);

        auto tw = jt::TweenAlpha<jt::SmartAnimation>::create(bp->getAnimation(), 0.1f, 255, 0);
        tw->setStartDelay(0.75f);
        add(tw);

        auto tw2 = jt::TweenColor<jt::SmartAnimation>::create(
            bp->getAnimation(), 0.4f, jt::colors::White, jt::colors::Red);
        tw2->setStartDelay(0.4f);
        add(tw2);

        auto tw3 = jt::TweenScale<jt::SmartAnimation>::create(
            bp->getAnimation(), 0.9f, jt::vector2 { 1, 1 }, jt::vector2 { 3, 3 });
        add(tw3);
    }

    if (getAge() >= 5.0 || jt::InputManager::justPressed(jt::KeyCode::F1)) {
        getGame()->switchState(std::make_shared<State2>());
    }
}
