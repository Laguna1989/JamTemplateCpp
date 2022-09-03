#include "bubble_smoke.hpp"
#include <random/random.hpp>
#include <tweens/tween_alpha.hpp>
#include <tweens/tween_position.hpp>
#include <tweens/tween_scale.hpp>

void jt::BubbleSmoke::doCreate()
{
    m_particles = jt::ParticleSystem<jt::Shape, 100>::createPS(
        [this]() {
            auto shape = std::make_shared<jt::Shape>();
            shape->makeCircle(6, textureManager());
            shape->setScale({ 0.0f, 0.0f });
            shape->setShadow(jt::Color { 0, 0, 0, 120 }, jt::Vector2f { 2.0f, 2.0f });
            return shape;
        },
        [this](auto& s, auto const& pos) {
            auto const startPos = jt::Random::getRandomPointIn({ pos.x - 32, pos.y - 32, 64, 64 });
            auto const endPos = startPos + jt::Vector2f { 0, jt::Random::getFloat(-125, -50) };
            s->setPosition(startPos);

            auto twp = jt::TweenPosition::create(s, 1.5f, startPos, endPos);
            addTween(twp);

            std::shared_ptr<jt::Tween> tws
                = jt::TweenScale::create(s, 1.5f * jt::Random::getFloat(0.75f, 1.25f),
                    { 0.0f, 0.0f }, jt::Random::getRandomPointIn({ 0.5f, 0.5f, 0.25f, 0.25f }));
            tws->setAgePercentConversion([](float t) {
                jt::EaseFromPoints ease { std::deque<jt::Vector2f> { { 0.0f, 0.0f },
                    { 0.25f, 1.0f }, { 0.5f, 0.5f }, { 0.75f, 1.0f }, { 1.0f, 0.0f } } };
                return ease.easeIn(t, 0.0f, 1.0f);
            });
            addTween(tws);
        });
    m_particles->setGameInstance(getGame());
}

void jt::BubbleSmoke::doUpdate(float const elapsed)
{
    m_particles->update(elapsed);

    m_tweens.update(elapsed);

    m_fireTimer -= elapsed;
    if (m_fireTimer >= 0.0f) {
        m_particles->fire(1, m_smokePos);
    }
}
void jt::BubbleSmoke::doDraw() const { m_particles->draw(); }

void jt::BubbleSmoke::fire(jt::Vector2f const& pos)
{
    m_smokePos = pos;
    m_fireTimer = 0.25f;
}

void jt::BubbleSmoke::addTween(std::shared_ptr<jt::TweenInterface> tween) { m_tweens.add(tween); }
