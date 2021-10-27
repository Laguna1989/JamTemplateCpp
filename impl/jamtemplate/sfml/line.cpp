#include "line.hpp"
#include <SFML/Graphics.hpp>
#include <math_helper.hpp>

jt::Line::Line(jt::Vector2 lineVector)
    : m_lineVector { std::move(lineVector) }
    , m_color { jt::colors::White }

{
}

void jt::Line::doUpdate(float /*elapsed*/) { }

void jt::Line::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (!sptr) {
        return;
    }
    auto const startPosition = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
    auto const endPosition = startPosition
        + jt::Vector2 { m_lineVector.x() * m_scale.x(), m_lineVector.y() * m_scale.y() };

    sf::VertexArray line { sf::Lines, 2 };
    line[0] = sf::Vertex { startPosition, m_color };
    line[1] = sf::Vertex { endPosition, m_color };
    sptr->draw(line);
}

void jt::Line::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const
{
    auto const startPosition
        = getPosition() + getShakeOffset() + getOffset() + getCamOffset() + getShadowOffset();
    auto const endPosition = startPosition
        + jt::Vector2 { m_lineVector.x() * m_scale.x(), m_lineVector.y() * m_scale.y() }
        + getShadowOffset();

    sf::VertexArray line { sf::Lines, 2 };
    line[0] = sf::Vertex { startPosition, getFlashColor() };
    line[1] = sf::Vertex { endPosition, getFlashColor() };
    sptr->draw(line);
}
void jt::Line::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const
{
    auto const startPosition
        = getPosition() + getShakeOffset() + getOffset() + getCamOffset() + getShadowOffset();
    auto const endPosition = startPosition
        + jt::Vector2 { m_lineVector.x() * m_scale.x(), m_lineVector.y() * m_scale.y() }
        + getShadowOffset();

    sf::VertexArray line { sf::Lines, 2 };
    line[0] = sf::Vertex { startPosition, getShadowColor() };
    line[1] = sf::Vertex { endPosition, getShadowColor() };
    sptr->draw(line);
}

void jt::Line::doRotate(float d) { m_lineVector = jt::MathHelper::rotateBy(m_lineVector, d); }

void jt::Line::setColor(jt::Color const& col) { m_color = col; }
jt::Color jt::Line::getColor() const { return m_color; }

void jt::Line::setPosition(jt::Vector2 const& pos) { m_position = pos; }
jt::Vector2 jt::Line::getPosition() const { return m_position; }

jt::Rect jt::Line::getGlobalBounds() const { return jt::Rect {}; }
jt::Rect jt::Line::getLocalBounds() const { return jt::Rect {}; }

void jt::Line::setFlashColor(jt::Color const& col) { m_flashColor = col; }
jt::Color jt::Line::getFlashColor() const { return m_flashColor; }

void jt::Line::setScale(jt::Vector2 const& scale) { m_scale = scale; }
jt::Vector2 jt::Line::getScale() const { return m_scale; }

void jt::Line::setOrigin(jt::Vector2 const& origin) { m_origin = origin; }
jt::Vector2 jt::Line::getOrigin() const { return m_origin; }
