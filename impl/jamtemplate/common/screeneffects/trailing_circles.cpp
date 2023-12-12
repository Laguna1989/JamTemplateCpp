#include "trailing_circles.hpp"
#include <random/random.hpp>
#include <tweens/tween_alpha.hpp>
#include <algorithm>

void jt::TrailingCircles::doCreate()
{
    m_tweens = std::make_shared<jt::TweenCollection>();
    m_particles = ParticleSystemType::createPS(
        [this]() {
            auto a = std::make_shared<jt::Animation>();
            a->loadFromAseprite("assets/circles.aseprite", textureManager());
            a->play("idle");

            a->setOffset(jt::OffsetMode::CENTER);
            a->setPosition(jt::Vector2f { -2000.0f, -2000.0f });
            return a;
        },
        [this](auto& a, auto pos) {
            auto const alpha = std::clamp(
                static_cast<std::uint8_t>(jt::Random::getFloat(0.7f, 1.3f) * m_maxAlpha),
                std::uint8_t { 0u }, std::uint8_t { 255u });
            jt::Color startColor { 255u, 255u, 255u, alpha };
            a->setColor(startColor);
            a->setPosition(pos);
            a->play("idle", 0, true);
            a->update(0.0f);

            auto twa = jt::TweenAlpha::create(a,
                a->getCurrentAnimTotalTime() * jt::Random::getFloat(0.75f, 0.95f), startColor.a,
                0u);
            this->m_tweens->add(twa);
        });

    m_particles->setGameInstance(getGame());
}

void jt::TrailingCircles::doUpdate(float const elapsed)
{
    m_tweens->update(elapsed);
    m_particles->update(elapsed);

    if (m_maxDistance < 0.0f) {
        m_timer += elapsed;
        if (m_timerMax > 0) {
            if (m_timer >= m_timerMax) {
                m_timer = 0.0f;
                m_particles->fire(1, m_pos);
            }
        }
    }
}

void jt::TrailingCircles::doDraw() const
{
    if (!m_enabled) {
        return;
    }
    m_particles->draw();
}

void jt::TrailingCircles::setPosition(jt::Vector2f const& pos)
{
    if (m_maxDistance > 0) {
        m_summedUpDistance += jt::MathHelper::qlength(m_pos - pos);
        if (m_summedUpDistance >= m_maxDistance) {
            m_summedUpDistance = 0.0f;
            m_particles->fire(1, pos);
        }
    }
    m_pos = pos;
}

void jt::TrailingCircles::setTimerMax(float max) { m_timerMax = max; }

void jt::TrailingCircles::setMaxAlpha(std::uint8_t maxAlpha) { m_maxAlpha = maxAlpha; }

void jt::TrailingCircles::setZ(int zLayer)
{
    m_particles->forEach([zLayer](auto& anim) { anim->setZ(zLayer); });
}

void jt::TrailingCircles::setEnabled(bool enable) { m_enabled = enable; }

void jt::TrailingCircles::setMaxDistanceToSpawnCircle(float maxDistance)
{
    m_maxDistance = maxDistance;
}
