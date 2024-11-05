#include "render_window_lib.hpp"
#include "performance_measurement.hpp"
#include <sprite.hpp>
#include <tracy/Tracy.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

jt::RenderWindow::RenderWindow(unsigned int width, unsigned int height, std::string const& title)
{
    m_window
        = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, sf::Style::Close);
    m_window->setVerticalSyncEnabled(true);

    auto const returnValue = ImGui::SFML::Init(*m_window.get());
    if (!returnValue) {
        throw std::invalid_argument { "SFML ImGui initialization failed." };
    }

    m_size = jt::Vector2f { static_cast<float>(m_window->getSize().x),
        static_cast<float>(m_window->getSize().y) };
}

jt::RenderWindow::~RenderWindow()
{
    ImGui::SFML::Shutdown();
    m_window.reset();
}

std::shared_ptr<jt::RenderTargetLayer> jt::RenderWindow::createRenderTarget()
{
    return std::make_shared<jt::RenderTargetLayer>();
}

bool jt::RenderWindow::isOpen() const { return m_window->isOpen(); }

void jt::RenderWindow::checkForClose()
{
    sf::Event event {};

    while (m_window->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }
    }
}

jt::Vector2f jt::RenderWindow::getSize() const noexcept { return m_size; }

void jt::RenderWindow::draw(std::unique_ptr<jt::Sprite>& spr)
{
    ZoneScopedN("jt::RenderWindow::draw");
    if (!spr) [[unlikely]] {
        throw std::invalid_argument { "Cannot draw nullptr sprite" };
    }
    m_window->draw(spr->getSFSprite());
}

void jt::RenderWindow::display()
{
    ZoneScopedN("jt::RenderWindow::display");
    if (m_renderGui) {
        m_hasBeenUpdatedAlready = false;
        ImGui::SFML::Render(*m_window.get());
    }

    m_window->display();
    m_renderGui = false;
}

jt::Vector2f jt::RenderWindow::getMousePosition()
{
    auto const mousePositionInt = sf::Mouse::getPosition(*m_window);
    return jt::Vector2f { static_cast<float>(mousePositionInt.x),
        static_cast<float>(mousePositionInt.y) };
}

void jt::RenderWindow::setMouseCursorVisible(bool visible)
{
    m_window->setMouseCursorVisible(visible);
    m_isMouseCursorVisible = visible;
}

bool jt::RenderWindow::getMouseCursorVisible() const noexcept { return m_isMouseCursorVisible; }

void jt::RenderWindow::updateGui(float elapsed)
{
    ImGui::SFML::Update(*m_window.get(), sf::seconds(elapsed));
}

void jt::RenderWindow::startRenderGui() { m_renderGui = true; }

bool jt::RenderWindow::shouldProcessKeyboard() { return !ImGui::GetIO().WantCaptureKeyboard; }

bool jt::RenderWindow::shouldProcessMouse() { return !ImGui::GetIO().WantCaptureMouse; }
