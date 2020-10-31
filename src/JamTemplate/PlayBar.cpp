#include "PlayBar.hpp"
#include "Game.hpp"

namespace JamTemplate {

PlayBar::PlayBar(float width, float height)
    : m_current_value { 0.0f }
    , m_max_value { 1.0f }
    , m_width { width }
    , m_height { height }
{
    m_shape_full = sf::RectangleShape(sf::Vector2f { m_width, m_height });
    m_shape_full.setFillColor(sf::Color { 150, 150, 150 });

    m_shape_progress = sf::RectangleShape(sf::Vector2f { m_width, m_height * 0.9f });
    m_shape_progress.setFillColor(sf::Color { 255, 255, 255 });
    m_shape_progress.setPosition(sf::Vector2f { 0, m_height * 0.1f });
}

void PlayBar::setPosition(sf::Vector2f const& pos)
{
    m_shape_full.setPosition(pos);
    m_shape_progress.setPosition(pos + sf::Vector2f { 0, m_height * 0.1f });
}

void PlayBar::doCreate() { }

void PlayBar::setFrontColor(sf::Color const& col) { m_shape_progress.setFillColor(col); }
void PlayBar::setBackColor(sf::Color const& col) { m_shape_full.setFillColor(col); }

void PlayBar::doUpdate(float const /*elapsed*/)
{
    float value = static_cast<float>(m_current_value) / m_max_value;
    m_shape_progress.setScale(value, 1);
}

void PlayBar::doDraw() const
{
    getGame()->getRenderTarget()->draw(m_shape_full);
    getGame()->getRenderTarget()->draw(m_shape_progress);
}
} // namespace JamTemplate
