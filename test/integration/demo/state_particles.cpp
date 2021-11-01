#include "state_particles.h"
#include "random.hpp"
#include "state_select.hpp"
#include "tweens/tween_alpha.hpp"
#include "tweens/tween_scale.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

void StateParticles::doInternalCreate()
{
    m_particles = jt::ParticleSystem<jt::Shape, numberOfParticles>::createPS(
        []() {
            auto s = std::make_shared<jt::Shape>();
            s->makeRect(jt::Vector2 { 4, 4 });
            s->setOrigin({ 2, 2 });
            return s;
        },
        [this](auto s) {
            s->setPosition(jt::Random::getRandomPointIn(jt::Rect { 0, 0, 400, 300 }));

            auto twa = jt::TweenAlpha::create(s, 0.5, 255, 0);
            twa->setSkipFrames(1);
            add(twa);

            auto tws = jt::TweenScale::create(
                s, 0.5, jt::Vector2 { 1.0f, 1.0f }, jt::Vector2 { 2.0f, 2.0f });
            tws->setSkipFrames(1);
            add(tws);
        });

    add(m_particles);
}
void StateParticles::doInternalUpdate(float elapsed)
{
    m_particles->Fire(toFire);
    m_timeMeasurement.push(elapsed);
    if (getAge() >= 15) {
        getGame()->switchState(std::make_shared<StateSelect>());
        float avg = std::accumulate(m_timeMeasurement.cbegin(), m_timeMeasurement.cend(), 0.0f)
            / m_timeMeasurement.size();
        std::cout << "avg: " << numberOfParticles << " "
                  << " " << toFire << " " << avg << std::endl;
    }
}
void StateParticles::doInternalDraw() const { }
