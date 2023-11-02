#include "logging_render_window.hpp"

jt::LoggingRenderWindow::LoggingRenderWindow(
    jt::RenderWindowInterface& decoratee, jt::LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
    auto const size = m_decoratee.getSize();
    m_logger.info("RenderWindow constructed. Size (" + std::to_string(static_cast<int>(size.x))
            + ", " + std::to_string(static_cast<int>(size.y)) + ")",
        { "jt", "RenderWindow" });
}

bool jt::LoggingRenderWindow::isOpen() const
{
    m_logger.verbose("isOpen", { "jt", "RenderWindow" });
    return m_decoratee.isOpen();
}

void jt::LoggingRenderWindow::checkForClose()
{
    m_logger.verbose("checkForClose", { "jt", "RenderWindow" });
    m_decoratee.checkForClose();
}

std::shared_ptr<jt::RenderTargetLayer> jt::LoggingRenderWindow::createRenderTarget()
{
    m_logger.debug("createRenderTarget", { "jt", "RenderWindow" });
    return m_decoratee.createRenderTarget();
}

jt::Vector2f jt::LoggingRenderWindow::getSize() const
{
    auto const size = m_decoratee.getSize();
    m_logger.verbose(
        std::string { "getSize: (" } + std::to_string(size.x) + ", " + std::to_string(size.y) + ")",
        { "jt", "RenderWindow" });
    return size;
}

void jt::LoggingRenderWindow::draw(std::unique_ptr<jt::Sprite>& sprite)
{
    m_logger.verbose("draw sprite", { "jt", "RenderWindow" });
    m_decoratee.draw(sprite);
}

void jt::LoggingRenderWindow::display()
{
    m_logger.verbose("display", { "jt", "RenderWindow" });
    m_decoratee.display();
}

jt::Vector2f jt::LoggingRenderWindow::getMousePosition()
{
    m_logger.verbose("getMousePosition", { "jt", "RenderWindow" });
    return m_decoratee.getMousePosition();
}

void jt::LoggingRenderWindow::setMouseCursorVisible(bool visible)
{
    m_logger.info("setMouseCursorVisible" + std::to_string(visible), { "jt", "RenderWindow" });
    m_decoratee.setMouseCursorVisible(visible);
}

bool jt::LoggingRenderWindow::getMouseCursorVisible() const
{
    m_logger.info("getMouseCursorVisible", { "jt", "RenderWindow" });
    return m_decoratee.getMouseCursorVisible();
}

void jt::LoggingRenderWindow::updateGui(float elapsed)
{
    m_logger.verbose("updateGui", { "jt", "RenderWindow" });
    m_decoratee.updateGui(elapsed);
}

void jt::LoggingRenderWindow::startRenderGui()
{
    m_logger.verbose("startRenderGui", { "jt", "RenderWindow" });
    m_decoratee.startRenderGui();
}

bool jt::LoggingRenderWindow::shouldProcessKeyboard()
{
    return m_decoratee.shouldProcessKeyboard();
}

bool jt::LoggingRenderWindow::shouldProcessMouse() { return m_decoratee.shouldProcessMouse(); }
