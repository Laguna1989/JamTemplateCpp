#include "bar.hpp"
#include <shape.hpp>
#include <iostream>
#include <stdexcept>

jt::Bar::Bar(
    float width, float height, bool horizontal, jt::TextureManagerInterface& textureManager)
    : m_valueMax { 1.0f }
    , m_valueCurrent { 0.0f }
    , m_width { width }
    , m_height { height }
    , m_horizontal { horizontal }
    , m_shapeFull { std::make_shared<jt::Shape>() }
    , m_shapeProgress { std::make_shared<jt::Shape>() }
{
    m_shapeFull->makeRect(jt::Vector2f { m_width, m_height }, textureManager);
    m_shapeFull->setColor(jt::colors::Gray);
    m_shapeFull->setIgnoreCamMovement(true);

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
    m_shapeProgress->setIgnoreCamMovement(true);
}

void jt::Bar::setFrontColor(jt::Color const& col) { m_shapeProgress->setColor(col); }
void jt::Bar::setBackColor(jt::Color const& col) { m_shapeFull->setColor(col); }

jt::Color jt::Bar::getBackColor() const { return m_shapeFull->getColor(); }

void jt::Bar::setCurrentValue(float value)
{
    m_valueCurrent = value;
    if (m_valueCurrent < 0) {
        m_valueCurrent = 0;
    } else if (m_valueCurrent > m_valueMax) {
        m_valueCurrent = m_valueMax;
    }
}

float jt::Bar::getCurrentValue() const { return m_valueCurrent; }

void jt::Bar::setMaxValue(float max)
{
    if (max < 0) {
        throw std::invalid_argument { "max value can not be negative" };
    }
    m_valueMax = max;
}

float jt::Bar::getMaxValue() const { return m_valueMax; }

float jt::Bar::getValueFraction() const { return m_valueCurrent / m_valueMax; }

void jt::Bar::doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    m_shapeFull->draw(sptr);
    m_shapeProgress->draw(sptr);
}

void jt::Bar::doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const /*sptr*/) const { }
void jt::Bar::doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    jt::Vector2f const oldPos = m_shapeFull->getPosition();
    jt::Color const oldCol = m_shapeFull->getColor();

    m_shapeFull->setPosition(oldPos + getShadowOffset());
    m_shapeFull->setColor(getShadowColor());
    m_shapeFull->draw(sptr);

    m_shapeFull->setPosition(oldPos);
    m_shapeFull->setColor(oldCol);
}

void jt::Bar::doUpdate(float elapsed)
{
    float const value = static_cast<float>(m_valueCurrent) / m_valueMax;
    auto const scaleFullShape = m_shapeFull->getScale();

    m_shapeFull->setPosition(m_position + getShakeOffset() + getOffset());

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

void jt::Bar::doRotate(float /*rot*/) { }

void jt::Bar::setColor(jt::Color const& col) { setFrontColor(col); }
jt::Color jt::Bar::getColor() const { return m_shapeProgress->getColor(); }

void jt::Bar::setPosition(jt::Vector2f const& pos) { m_position = pos; }

jt::Vector2f jt::Bar::getPosition() const { return m_position; }

jt::Rectf jt::Bar::getGlobalBounds() const { return m_shapeFull->getGlobalBounds(); }
jt::Rectf jt::Bar::getLocalBounds() const { return m_shapeFull->getLocalBounds(); }

void jt::Bar::setScale(jt::Vector2f const& scale)
{
    m_shapeFull->setScale(scale);
    m_shapeProgress->setScale(scale);
}

jt::Vector2f jt::Bar::getScale() const { return m_shapeFull->getScale(); }
