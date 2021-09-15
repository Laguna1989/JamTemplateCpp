#include "state_particles.h"
#include "state_select.hpp"
#include "tween_alpha.hpp"
#include "tween_scale.hpp"

void StateParticles::doInternalCreate()
{
    m_particles = jt::ParticleSystem<jt::Shape, 500>::create(
        []() {
            auto s = std::make_shared<jt::Shape>();
            s->makeRect(jt::Vector2 { 4, 4 });
            s->setOrigin({ 2, 2 });
            return s;
        },
        [this](auto s) {
            s->setPosition(jt::Random::getRandomPointin(jt::Rect { 0, 0, 400, 300 }));

            auto twa = jt::TweenAlpha<jt::DrawableInterface>::create(s, 0.5, 255, 0);
            twa->setSkipFrames(1);
            add(twa);

            auto tws = jt::TweenScale<jt::DrawableInterface>::create(
                s, 0.5, jt::Vector2 { 1.0f, 1.0f }, jt::Vector2 { 2.0f, 2.0f });
            tws->setSkipFrames(1);
            add(tws);
        });

    add(m_particles);
}
void StateParticles::doInternalUpdate(float elapsed)
{
    m_particles->Fire(20);

    if (getAge() >= 5) {
        getGame()->switchState(std::make_shared<StateSelect>());
    }
}
void StateParticles::doInternalDraw() const { }
