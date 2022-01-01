#include "bar.hpp"
#include "shape.hpp"
#include <iostream>
#include <stdexcept>

namespace jt {

Bar::Bar(float width, float height, bool horizontal, jt::TextureManagerInterface& textureManager)
    : m_valueMax { 1.0f }
    , m_valueCurrent { 0.0f }
    , m_width { width }
    , m_height { height }
    , m_horizontal { horizontal }
{
    m_shapeFull = std::make_shared<jt::Shape>();
    m_shapeFull->makeRect(jt::Vector2f { m_width, m_height }, textureManager);
    m_shapeFull->setColor(jt::colors::Gray);

    m_shapeProgress = std::make_shared<jt::Shape>();
    if (m_horizontal) {
        auto const progressHeightFactor = 0.9f;
        m_shapeProgress->makeRect(
            jt::Vector2f { m_width, m_height * progressHeightFactor }, textureManager);
        m_shapeProgress->setPosition(jt::Vector2f { 0, m_height * m_progressYOffsetFraction });
    } else {
        m_shapeProgress->makeRect(jt::Vector2f { m_width - 2, m_height }, textureManager);
        m_shapeProgress->setPosition(jt::Vector2f { 0 + 1, m_height });
    }
    m_shapeProgress->setColor(jt::colors::White);
}

void Bar::setFrontColor(jt::Color const& col) { m_shapeProgress->setColor(col); }
void Bar::setBackColor(jt::Color const& col) { m_shapeFull->setColor(col); }

jt::Color Bar::getBackColor() const { return m_shapeFull->getColor(); }

void Bar::setCurrentValue(float value)
{
    m_valueCurrent = value;
    if (m_valueCurrent < 0) {
        m_valueCurrent = 0;
    } else if (m_valueCurrent > m_valueMax) {
        m_valueCurrent = m_valueMax;
    }
}

float Bar::getCurrentValue() const { return m_valueCurrent; }

void Bar::setMaxValue(float max)
{
    if (max < 0) {
        throw std::invalid_argument { "max value can not be negative" };
    }
    m_valueMax = max;
}

float Bar::getMaxValue() const { return m_valueMax; }

float Bar::getValueFraction() const { return m_valueCurrent / m_valueMax; }

void Bar::doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    m_shapeFull->draw(sptr);
    m_shapeProgress->draw(sptr);
}

void Bar::doDrawFlash(std::shared_ptr<jt::RenderTarget> const /*sptr*/) const { }
void Bar::doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    jt::Vector2f const oldPos = m_shapeFull->getPosition();
    jt::Color const oldCol = m_shapeFull->getColor();

    m_shapeFull->setPosition(oldPos + getShadowOffset());
    m_shapeFull->setColor(getShadowColor());
    m_shapeFull->draw(sptr);

    m_shapeFull->setPosition(oldPos);
    m_shapeFull->setColor(oldCol);
}

void Bar::doUpdate(float elapsed)
{
    float const value = static_cast<float>(m_valueCurrent) / m_valueMax;
    auto const scaleFullShape = m_shapeFull->getScale();
    if (m_horizontal) {
        m_shapeProgress->setScale(jt::Vector2f { value * scaleFullShape.x, scaleFullShape.y });
    } else {
        m_shapeProgress->setScale(jt::Vector2f { scaleFullShape.x, value * scaleFullShape.y });
        m_shapeProgress->setPosition(jt::Vector2f { m_shapeFull->getPosition().x + 1,
            m_shapeFull->getPosition().y + (1 - value) * m_height });
    }
    m_shapeFull->update(elapsed);
    m_shapeProgress->update(elapsed);
}
void Bar::doFlash(float /*t*/, jt::Color /*col = jt::colors::White*/) { }
void Bar::doRotate(float /*rot*/) { }

void Bar::setColor(jt::Color const& col) { setFrontColor(col); }
jt::Color Bar::getColor() const { return m_shapeProgress->getColor(); }

void Bar::setPosition(jt::Vector2f const& pos)
{
    m_shapeFull->setPosition(pos);
    m_shapeProgress->setPosition(pos + jt::Vector2f { 0, m_height * m_progressYOffsetFraction });
}

jt::Vector2f Bar::getPosition() const { return m_shapeFull->getPosition(); }

jt::Rectf Bar::getGlobalBounds() const { return m_shapeFull->getGlobalBounds(); }
jt::Rectf Bar::getLocalBounds() const { return m_shapeFull->getLocalBounds(); }

void Bar::setFlashColor(jt::Color const& col) { m_flashColor = col; }
jt::Color Bar::getFlashColor() const { return m_flashColor; }

void Bar::setScale(jt::Vector2f const& scale)
{
    m_shapeFull->setScale(scale);
    m_shapeProgress->setScale(scale);
}

jt::Vector2f Bar::getScale() const { return m_shapeFull->getScale(); }

void Bar::setOrigin(jt::Vector2f const& origin) { m_shapeFull->setOrigin(origin); }
jt::Vector2f Bar::getOrigin() const { return m_shapeFull->getOrigin(); }

} // namespace jt
