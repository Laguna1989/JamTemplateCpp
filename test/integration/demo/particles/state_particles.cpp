#include "state_particles.hpp"
#include "../state_select.hpp"
#include "lerp.hpp"
#include "random/random.hpp"
#include "tweens/tween_alpha.hpp"
#include "tweens/tween_color.hpp"
#include "tweens/tween_position.hpp"
#include "tweens/tween_scale.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

void StateParticles::doInternalCreate()
{
    createParticlesGlitter();
    createParticlesFire();
    auto rng = std::default_random_engine {};

    m_sparkParticles = jt::ParticleSystem<jt::Animation, 80>::createPS(
        [this, &rng]() {
            auto a = std::make_shared<jt::Animation>();
            std::vector<unsigned int> numbers = jt::MathHelper::numbersBetween(0u, 7u);

            std::shuffle(numbers.begin(), numbers.end(), rng);

            a->add("assets/spark.png", "spark", jt::Vector2u { 24, 24 }, numbers,
                jt::Random::getFloat(0.05f, 0.175f), getGame()->gfx().textureManager());
            a->play("spark");
            a->setOrigin(jt::Vector2f { 12, 12 });
            a->setPosition(jt::Vector2f { -2000.0f, -2000.0f });
            return a;
        },
        [](auto a) {
            auto startPosition = jt::Random::getRandomPointIn(jt::Rectf { 210, 50, 80, 200 });
            a->setPosition(startPosition);
            a->setRotation(jt::Random::getFloat(0.0f, 360.0f));
        });
    add(m_sparkParticles);
}
void StateParticles::createParticlesFire()
{
    m_particlesFire = jt::ParticleSystem<jt::Shape, 200>::createPS(
        [this]() {
            auto s = jt::dh::createShapeCircle(
                20, jt::MakeColor::FromHSV(45, 80, 100), getGame()->gfx().textureManager());
            s->setOrigin(jt::Vector2f { 20, 20 });
            s->setPosition(jt::Vector2f { -2000.0f, -2000.0f });
            s->setScale(jt::Vector2f { 0.5f, 0.5f });
            return s;
        },
        [this](auto s) {
            auto totalTime = 0.9f;

            auto startPosition = jt::Random::getRandomPointIn(jt::Rectf { 155, 250, 10, 0 });
            s->setPosition(startPosition);

            s->setScale(jt::Vector2f { 0.5f, 0.5f });

            jt::TweenAlpha::Sptr twaIn = jt::TweenAlpha::create(s, 0.1f, 0, 255);
            twaIn->setSkipFrames(1);
            add(twaIn);

            jt::TweenAlpha::Sptr twaOut = jt::TweenAlpha::create(s, totalTime - 0.25f, 255, 0);
            twaOut->setSkipFrames(1);
            twaOut->setStartDelay(0.25f);
            twaOut->setAgePercentConversion([](float t) {
                t = jt::MathHelper::clamp(t, 0.0f, 1.0f);
                return 0.9f * jt::Lerp::cubic(0.0f, 1.0f, t) + 0.1f * t;
            });
            add(twaOut);

            auto tws = jt::TweenScale::create(
                s, totalTime - 0.1f, jt::Vector2f { 0.5f, 0.5f }, jt::Vector2f { 1.0f, 1.0f });
            tws->setSkipFrames(1);
            tws->setStartDelay(0.1f);
            add(tws);

            auto endPosition
                = startPosition + jt::Random::getRandomPointIn(jt::Rectf { -30, -150, 60, 40 });
            jt::TweenPosition::Sptr twp
                = jt::TweenPosition::create(s, totalTime, startPosition, endPosition);
            twp->setSkipFrames(1);
            twp->setAgePercentConversion([](float t) {
                t = jt::MathHelper::clamp(t, 0.0f, 1.0f);
                return 0.5f * jt::Lerp::cubic(0.0f, 1.0f, t) + 0.5f * t;
            });
            add(twp);

            auto intermediateColor = jt::MakeColor::FromHSV(0, 60, 67);
            auto finalColor = jt::MakeColor::FromHSV(318, 42, 27);

            float const fraction = jt::Random::getFloat(0.6f, 0.7f);
            jt::TweenColor::Sptr twc1 = jt::TweenColor::create(
                s, totalTime * fraction, jt::MakeColor::FromHSV(45, 80, 100), intermediateColor);
            twc1->setSkipFrames(1);
            twc1->addCompleteCallback(
                [this, totalTime, fraction, s, intermediateColor, finalColor]() {
                    jt::TweenColor::Sptr twc2 = jt::TweenColor::create(
                        s, totalTime * (1.0f - fraction), intermediateColor, finalColor);
                    twc2->setSkipFrames(1);
                    add(twc2);
                });
            add(twc1);
        });
    add(m_particlesFire);
}
void StateParticles::createParticlesGlitter()
{
    m_particlesGlitter = jt::ParticleSystem<jt::Shape, numberOfParticles>::createPS(
        [this]() {
            auto s = std::make_shared<jt::Shape>();
            s->makeRect(jt::Vector2f { 4, 4 }, getGame()->gfx().textureManager());
            s->setOrigin({ 2, 2 });
            return s;
        },
        [this](auto s) {
            s->setPosition(jt::Random::getRandomPointIn(jt::Rectf { 0, 0, 100, 300 }));

            auto twa = jt::TweenAlpha::create(s, 0.5, 255, 0);
            twa->setSkipFrames(1);
            add(twa);

            auto tws = jt::TweenScale::create(
                s, 0.5, jt::Vector2f { 1.0f, 1.0f }, jt::Vector2f { 2.0f, 2.0f });
            tws->setSkipFrames(1);
            add(tws);
        });
    add(m_particlesGlitter);
}
void StateParticles::doInternalUpdate(float elapsed)
{
    m_particlesGlitter->Fire(toFire);
    m_particlesFire->Fire(1);
    m_sparkParticles->Fire(1);

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }

    m_timeMeasurement.push(elapsed);
    if (getAge() >= 15) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
        float avg = std::accumulate(m_timeMeasurement.cbegin(), m_timeMeasurement.cend(), 0.0f)
            / m_timeMeasurement.size();
        std::cout << "avg: " << numberOfParticles << " "
                  << " " << toFire << " " << avg << std::endl;
    }
}
void StateParticles::doInternalDraw() const { }
std::string StateParticles::getName() const { return "Particles"; }
