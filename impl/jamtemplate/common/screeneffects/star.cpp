#include "star.hpp"
#include "math_helper.hpp"
#include <game_interface.hpp>
#include <random/random.hpp>
#include <screeneffects/screen_wrap.hpp>
#include <algorithm>

void jt::Star::setPosition(jt::Vector2f const& screenSizeHint)
{
    if (!m_shape) {
        throw std::logic_error { "Cannot set star position before create has been called." };
    }
    auto const p = jt::MathHelper::castToInteger(
        jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, screenSizeHint.x, screenSizeHint.y }));

    m_shape->setPosition(p);
    m_shape->setScreenSizeHint(screenSizeHint);

    auto const sg
        = jt::Vector2f { m_glow->getLocalBounds().width, m_glow->getLocalBounds().height };
    auto const ss
        = jt::Vector2f { m_shape->getLocalBounds().width, m_shape->getLocalBounds().height };
    m_glow->setPosition({ p.x - sg.x / 2 + ss.x / 2, p.y - sg.y / 2 + ss.x / 2 });
}

void jt::Star::setColor(jt::Color const& col)
{
    if (!m_shape) {
        throw std::logic_error { "Cannot set star color before create has been called." };
    }
    m_shape->setColor(col);
    auto gc = col;
    gc.a = m_starAlphaMax;
    m_glow->setColor(gc);
}

void jt::Star::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    int size = 1;
    if (jt::Random::getChance(0.2f)) {
        size = 2;
    }
    m_shape->makeCircle(static_cast<float>(size), getGame()->gfx().textureManager());
    m_shape->setCamMovementFactor(0.5f);

    m_glowSize = jt::Random::getInt(12, 40);
    m_glow = std::make_shared<jt::Sprite>(
        "#g#" + std::to_string(m_glowSize) + "#100", textureManager());

    m_rand1 = jt::Random::getFloat(0.2f, 0.5f);
    m_rand2 = jt::Random::getFloat(0.0f, 1.5f);
    m_rand3 = jt::Random::getFloat(0.5f, 1.0f);

    m_starAlphaMax = static_cast<std::uint8_t>(jt::Random::getInt(30, 100));

    auto const sizeGlow
        = jt::Vector2f { m_glow->getLocalBounds().width, m_glow->getLocalBounds().height };
    auto const sizeStar
        = jt::Vector2f { m_shape->getLocalBounds().width, m_shape->getLocalBounds().height };
    m_glowOffset = 0.5f * (sizeGlow - sizeStar);
}

void jt::Star::doUpdate(float const elapsed)
{
    updateStarBrightness();

    jt::wrapOnScreen(*m_shape.get(), m_glowSize);
    m_glow->setPosition(m_shape->getPosition() - m_glowOffset);

    m_shape->update(elapsed);
    m_glow->update(elapsed);
}

void jt::Star::updateStarBrightness()
{
    float const t = getAge() * m_rand1 + m_rand2;
    float const a = sin(t) * sin(t);
    std::uint8_t const alpha = static_cast<std::uint8_t>(a * 255.0f * m_rand3);

    auto col = m_shape->getColor();
    col.a = alpha;
    m_shape->setColor(col);
    col.a = std::clamp(col.a, std::uint8_t { 20u }, m_starAlphaMax);
    m_glow->setColor(col);
}

void jt::Star::doDraw() const
{
    m_glow->draw(getGame()->gfx().target());
    m_shape->draw(getGame()->gfx().target());
}

void jt::Star::setCamMovementFactor(float factor)
{
    m_shape->setCamMovementFactor(factor);
    m_glow->setCamMovementFactor(factor);
}

void jt::Star::setZ(int zLayer)
{
    m_shape->setZ(zLayer);
    m_glow->setZ(zLayer);
}
