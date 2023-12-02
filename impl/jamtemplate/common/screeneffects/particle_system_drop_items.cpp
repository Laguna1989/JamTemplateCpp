#include "particle_system_drop_items.hpp"
#include <random/random.hpp>
#include <system_helper.hpp>
#include <tweens/tween_alpha.hpp>
#include <tweens/tween_position.hpp>

jt::ParticleSystemDropItems::ParticleSystemDropItems(
    std::string const& aseFileName, float radius, float time)
    : m_aseFileName { aseFileName }
    , m_radius { radius }
    , m_time { time }
{
}

void jt::ParticleSystemDropItems::doCreate()
{
    m_tweens = std::make_shared<jt::TweenCollection>();

    m_particles = jt::ParticleSystem<jt::Animation, 12u>::createPS(
        [this]() {
            auto a = std::make_shared<jt::Animation>();
            a->loadFromAseprite(m_aseFileName, textureManager());
            a->play(a->getRandomAnimationName());

            a->setOffset(jt::OffsetMode::CENTER);
            a->setPosition(jt::Vector2f { -2000.0f, -2000.0f });
            return a;
        },
        [this](auto& a, auto pos) {
            auto const tweenTime = m_time;
            a->setPosition(pos);
            a->setColor(jt::colors::White);
            a->update(0.0f);

            std::shared_ptr<jt::Tween> twp1 = jt::TweenPosition::create(
                a, tweenTime / 2.0f, pos, pos + jt::Random::getRandomPointOnCircle(m_radius));
            twp1->addCompleteCallback([tweenTime, &a]() { a->flicker(tweenTime / 2.0f); });
            m_tweens->add(twp1);

            constexpr auto fadeOutDuration = 0.05f;
            std::shared_ptr<jt::Tween> const twa
                = jt::TweenAlpha::create(a, fadeOutDuration, 255u, 0u);
            twa->setStartDelay(tweenTime - fadeOutDuration);
            m_tweens->add(twa);
        });
    m_particles->setGameInstance(getGame());
    m_particles->create();
}

void jt::ParticleSystemDropItems::doUpdate(float const elapsed)
{
    m_tweens->update(elapsed);

    m_particles->update(elapsed);
}

void jt::ParticleSystemDropItems::doDraw() const { m_particles->draw(); }

void jt::ParticleSystemDropItems::fire(int number, jt::Vector2f const& pos)
{
    m_particles->fire(number, pos);
}
