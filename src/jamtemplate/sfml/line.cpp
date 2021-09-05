#include "line.hpp"
#include <SFML/Graphics.hpp>

jt::Line::Line(jt::Vector2 lineVector)
    : m_lineVector { lineVector }
    , m_color { jt::colors::White }

{
}

void jt::Line::doUpdate(float /*elapsed*/) { }

void jt::Line::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    auto const startPosition = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
    auto const endPosition = startPosition + m_lineVector;

    sf::Vertex line[]
        = { sf::Vertex { startPosition, m_color }, sf::Vertex { endPosition, m_color } };
    sptr->draw(line, 2, sf::Lines);
}

void jt::Line::doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const { }
void jt::Line::doDrawShadow(std::shared_ptr<jt::renderTarget> const /*sptr*/) const { }

void jt::Line::doRotate(float d) { }

void jt::Line::setColor(jt::Color const& col) { m_color = col; }
const jt::Color jt::Line::getColor() const { return m_color; }

void jt::Line::setPosition(jt::Vector2 const& pos) { m_position = pos; }
const jt::Vector2 jt::Line::getPosition() const { return m_position; }

jt::Rect const jt::Line::getGlobalBounds() const { return jt::Rect {}; }
jt::Rect const jt::Line::getLocalBounds() const { return jt::Rect {}; }

void jt::Line::setFlashColor(jt::Color const& col) { }
const jt::Color jt::Line::getFlashColor() const { return jt::colors::White; }

void jt::Line::setScale(jt::Vector2 const& scale) { }
const jt::Vector2 jt::Line::getScale() const { return jt::Vector2 { 1.0f, 1.0f }; }

void jt::Line::setOrigin(jt::Vector2 const& origin) { }
const jt::Vector2 jt::Line::getOrigin() const { return jt::Vector2 { 0.0f, 0.0f }; }
