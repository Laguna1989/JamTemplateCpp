#include "line.hpp"
#include "color_lib.hpp"
#include "math_helper.hpp"
#include "vector_lib.hpp"
#include <SFML/Graphics.hpp>

jt::Line::Line(jt::Vector2f lineVector)
    : m_lineVector { std::move(lineVector) }
    , m_color { jt::colors::White }

{
}

void jt::Line::doUpdate(float /*elapsed*/) { }

void jt::Line::doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    if (!sptr) {
        return;
    }
    auto const startPosition = getPosition() + getShakeOffset() + getOffset() + getCamOffset();
    auto const endPosition
        = startPosition + jt::Vector2f { m_lineVector.x * m_scale.x, m_lineVector.y * m_scale.y };

    sf::VertexArray line { sf::Lines, 2 };
    line[0] = sf::Vertex { toLib(startPosition), toLib(m_color) };
    line[1] = sf::Vertex { toLib(endPosition), toLib(m_color) };
    sptr->draw(line);
}

void jt::Line::doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    auto const startPosition
        = getPosition() + getShakeOffset() + getOffset() + getCamOffset() + getShadowOffset();
    auto const endPosition = startPosition
        + jt::Vector2f { m_lineVector.x * m_scale.x, m_lineVector.y * m_scale.y }
        + getShadowOffset();

    sf::VertexArray line { sf::Lines, 2 };
    line[0] = sf::Vertex { toLib(startPosition), toLib(getFlashColor()) };
    line[1] = sf::Vertex { toLib(endPosition), toLib(getFlashColor()) };
    sptr->draw(line);
}
void jt::Line::doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    auto const startPosition
        = getPosition() + getShakeOffset() + getOffset() + getCamOffset() + getShadowOffset();
    auto const endPosition = startPosition
        + jt::Vector2f { m_lineVector.x * m_scale.x, m_lineVector.y * m_scale.y }
        + getShadowOffset();

    sf::VertexArray line { sf::Lines, 2 };
    line[0] = sf::Vertex { toLib(startPosition), toLib(getShadowColor()) };
    line[1] = sf::Vertex { toLib(endPosition), toLib(getShadowColor()) };
    sptr->draw(line);
}

void jt::Line::doRotate(float d) { m_lineVector = jt::MathHelper::rotateBy(m_lineVector, d); }

void jt::Line::setColor(jt::Color const& col) { m_color = col; }
jt::Color jt::Line::getColor() const { return m_color; }

void jt::Line::setPosition(jt::Vector2f const& pos) { m_position = pos; }
jt::Vector2f jt::Line::getPosition() const { return m_position; }

jt::Rectf jt::Line::getGlobalBounds() const { return jt::Rectf {}; }
jt::Rectf jt::Line::getLocalBounds() const { return jt::Rectf {}; }

void jt::Line::setFlashColor(jt::Color const& col) { m_flashColor = col; }
jt::Color jt::Line::getFlashColor() const { return m_flashColor; }

void jt::Line::setScale(jt::Vector2f const& scale) { m_scale = scale; }
jt::Vector2f jt::Line::getScale() const { return m_scale; }

void jt::Line::setOrigin(jt::Vector2f const& origin) { m_origin = origin; }
jt::Vector2f jt::Line::getOrigin() const { return m_origin; }
