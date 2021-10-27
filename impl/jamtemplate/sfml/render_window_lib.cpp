#include "render_window_lib.hpp"
#include "sprite.hpp"
#include <SFML/Graphics.hpp>

namespace jt {

RenderWindow::RenderWindow(unsigned int width, unsigned int height, std::string const& title)
{
    m_window
        = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Close);
    m_window->setVerticalSyncEnabled(true);
}

std::shared_ptr<jt::renderTarget> RenderWindow::createRenderTarget()
{
    return std::make_shared<jt::renderTarget>();
}

bool RenderWindow::isOpen() const { return m_window->isOpen(); }

void RenderWindow::checkForClose()
{
    sf::Event event {};
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

void RenderWindow::draw(std::unique_ptr<jt::Sprite>& spr)
{
    if (!spr) {
        throw std::invalid_argument { "Cannot draw nullptr sprite" };
    }
    m_window->draw(spr->getSFSprite());
}

void RenderWindow::display() { m_window->display(); }

jt::Vector2 RenderWindow::getMousePosition()
{
    auto const mpi = sf::Mouse::getPosition(*m_window);
    return jt::Vector2 { static_cast<float>(mpi.x), static_cast<float>(mpi.y) };
}

void RenderWindow::setMouseCursorVisible(bool visible)
{
    m_window->setMouseCursorVisible(visible);
    m_isMouseCursorVisible = visible;
}
bool RenderWindow::getMouseCursorVisible(void) const { return m_isMouseCursorVisible; }

} // namespace jt
