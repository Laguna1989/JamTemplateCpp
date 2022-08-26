#include "star.hpp"
#include <game_interface.hpp>
#include <random/random.hpp>
#include <screeneffects/screen_wrap.hpp>
#include <iostream>

void jt::Star::setPosition(jt::Vector2f const& screenSizeHint)
{
    if (!m_shape) {
        throw std::logic_error { "Cannot set star position before create has been called." };
    }
    auto p = jt::Random::getRandomPointIn(
        jt::Rectf { 0.0f, 0.0f, screenSizeHint.x, screenSizeHint.y });

    p.x = static_cast<float>(static_cast<int>(p.x));
    p.y = static_cast<float>(static_cast<int>(p.y));

    m_shape->setPosition(p);
    m_shape->setScreenSizeHint(screenSizeHint);
}

void jt::Star::setColor(jt::Color const& col)
{
    if (!m_shape) {
        throw std::logic_error { "Cannot set star color before create has been called." };
    }
    m_shape->setColor(col);
}

void jt::Star::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeCircle(
        static_cast<float>(jt::Random::getInt(1, 2)), getGame()->gfx().textureManager());
    m_shape->setCamMovementFactor(0.5f);
    m_rand1 = jt::Random::getFloat(0.2f, 0.5f);
    m_rand2 = jt::Random::getFloat(0.0f, 1.5f);
    m_rand3 = jt::Random::getFloat(0.5f, 1.0f);
}

void jt::Star::doUpdate(float const elapsed)
{
    m_shape->update(elapsed);

    //    std::cout << m_shape->isVisible() << " " << m_shape->getScreenPosition().x << std::endl;
    float const t = getAge() * m_rand1 + m_rand2;
    float const a = sin(t) * sin(t);
    std::uint8_t const alpha = static_cast<std::uint8_t>(a * 255.0f * m_rand3);

    auto col = m_shape->getColor();
    col.a = alpha;
    m_shape->setColor(col);
    jt::wrapOnScreen(*m_shape.get(), 0.0f);
}

void jt::Star::doDraw() const { m_shape->draw(getGame()->gfx().target()); }
void jt::Star::setCamMovementFactor(float factor) { m_shape->setCamMovementFactor(factor); }
