#include "state_explosion.hpp"
#include "game_interface.hpp"
#include "input_manager.hpp"
#include "object.hpp"
#include "random.hpp"
#include "state_select.hpp"
#include "timer.hpp"
#include "tweens/tween_alpha.hpp"
#include "tweens/tween_color.hpp"
#include "tweens/tween_scale.hpp"

void StateExplosion::doInternalCreate()
{
    using jt::Timer;

    getGame()->getCamera()->shake(0.5f, 2.0f);
    jt::Timer::Sptr t
        = std::make_shared<Timer>(0.6f, [this]() { getGame()->getCamera()->shake(0.5f, 10.0f); });
    add(t);
}

void StateExplosion::doInternalUpdate(float const /*elapsed*/)
{
    unsigned int N = 1;
    for (unsigned int i = 0; i != N; ++i) {
        Object::Sptr bp = std::make_shared<Object>();
        add(bp);
        using jt::Timer;
        Timer::Sptr t
            = std::make_shared<Timer>(jt::Random::getFloat(0.125, 3), [bp]() { bp->Flash(); });
        add(t);

        auto tw = jt::TweenAlpha::create(bp->getAnimation(), 0.1f, 255, 0);
        tw->setStartDelay(0.75f);
        add(tw);

        auto tw2
            = jt::TweenColor::create(bp->getAnimation(), 0.4f, jt::colors::White, jt::colors::Red);
        tw2->setStartDelay(0.4f);
        add(tw2);

        auto tw3 = jt::TweenScale::create(
            bp->getAnimation(), 0.9f, jt::Vector2 { 1, 1 }, jt::Vector2 { 3, 3 });
        add(tw3);
    }

    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->switchState(std::make_shared<StateSelect>());
    }
}
