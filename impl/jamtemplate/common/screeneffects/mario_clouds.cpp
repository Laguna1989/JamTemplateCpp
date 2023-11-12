#include "mario_clouds.hpp"
#include <random/random.hpp>
#include <screeneffects/screen_wrap.hpp>
#include <system_helper.hpp>

jt::MarioClouds::MarioClouds(
    std::size_t numberOfClouds, jt::Vector2f const& mapSize, jt::Vector2f const& margin)
    : m_numberOfClouds { numberOfClouds }
    , m_mapSize { mapSize }
    , m_margin { margin }
{
}

void jt::MarioClouds::setEnabled(bool enable) { m_enabled = enable; }

void jt::MarioClouds::setScale(jt::Vector2f const& scale)
{
    for (auto& c : m_clouds) {
        c->setScale(scale);
    }
}

void jt::MarioClouds::setShadowOffset(jt::Vector2f const& offset)
{
    for (auto& c : m_clouds) {
        c->setShadow(jt::Color { 10, 10, 10, 30 }, offset);
    }
}

void jt::MarioClouds::doCreate()
{
    for (auto i = 0u; i != m_numberOfClouds; ++i) {
        auto anim = std::make_shared<jt::Animation>();
        anim->loadFromAseprite("assets/marioclouds.aseprite", textureManager());
        anim->play(anim->getRandomAnimationName());
        anim->setBlendMode(jt::BlendMode::ADD);
        anim->setColor(jt::Color { 255, 255, 255, 200 });

        anim->setShadow(jt::Color { 10, 10, 10, 30 }, jt::Vector2f { 18, 14 });

        anim->setPosition(jt::Random::getRandomPointIn(jt::Rectf { -m_margin.x, -m_margin.y,
            m_mapSize.x + m_margin.x * 2, m_mapSize.y + m_margin.y * 2 }));
        m_clouds.push_back(anim);
    }
}

void jt::MarioClouds::doUpdate(float const elapsed)
{
    if (!m_enabled) {
        return;
    }
    jt::Vector2f const velocity { 5, 0 };
    for (auto& c : m_clouds) {

        auto pos = c->getPosition();
        pos += elapsed * velocity;

        if (pos.x > m_mapSize.x + m_margin.x) {
            pos.x = -m_margin.x;
        }
        c->setPosition(pos);

        c->update(elapsed);
    }
}

void jt::MarioClouds::doDraw() const
{
    if (!m_enabled) {
        return;
    }
    for (auto& c : m_clouds) {
        c->draw(renderTarget());
    }
}

void jt::MarioClouds::setZ(int zLayer)
{
    for (auto& c : m_clouds) {
        c->setZ(zLayer);
    }
}
