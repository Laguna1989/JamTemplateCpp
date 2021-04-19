#include "RenderWindow_lib.hpp"
#include "Sprite.hpp"
#include <SFML/Graphics.hpp>

namespace jt {

std::weak_ptr<sf::View> RenderWindow::s_view;

RenderWindow::RenderWindow(unsigned int width, unsigned int height, std::string const& title)
{
    m_window
        = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Close);
    m_window->setVerticalSyncEnabled(true);
}

std::shared_ptr<jt::renderTarget> RenderWindow::createRenderTarget()
{
    auto window = std::make_shared<jt::renderTarget>();
    return window;
}

bool RenderWindow::isOpen() const { return m_window->isOpen(); }

void RenderWindow::checkForClose()
{
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }
    }
}

jt::Vector2 RenderWindow::getSize() const
{
    return jt::Vector2 { static_cast<float>(m_window->getSize().x),
        static_cast<float>(m_window->getSize().y) };
}

void RenderWindow::draw(std::shared_ptr<jt::Sprite> spr)
{
    if (!m_window) {
        throw std::invalid_argument { "Cannot draw on nullptr window" };
    }
    if (!spr) {
        throw std::invalid_argument { "Cannot draw nullptr sprite" };
    }
    m_window->draw(spr->getSFSprite());
}

void RenderWindow::display() { m_window->display(); }

jt::Vector2 RenderWindow::getMousePosition()
{
    if (s_view.expired()) {
        return jt::Vector2 { 0, 0 };
    }
    auto view = s_view.lock();
    return m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window), *view);
}

jt::Vector2 RenderWindow::getMousePositionScreen(float zoom)
{
    return m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)) / zoom;
}

} // namespace jt
