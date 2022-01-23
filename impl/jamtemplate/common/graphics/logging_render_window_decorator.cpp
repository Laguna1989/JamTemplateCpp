#include "logging_render_window_decorator.hpp"

namespace jt {

LoggingRenderWindowDecorator::LoggingRenderWindowDecorator(
    RenderWindowInterface& decoratee, LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

bool LoggingRenderWindowDecorator::isOpen() const
{
    m_logger.verbose("isOpen", { "jt", "RenderWindow" });
    return m_decoratee.isOpen();
}

void LoggingRenderWindowDecorator::checkForClose()
{
    m_logger.verbose("checkForClose", { "jt", "RenderWindow" });
    m_decoratee.checkForClose();
}
std::shared_ptr<jt::RenderTarget> LoggingRenderWindowDecorator::createRenderTarget()
{
    m_logger.debug("createRenderTarget", { "jt", "RenderWindow" });
    return m_decoratee.createRenderTarget();
}

Vector2f LoggingRenderWindowDecorator::getSize() const
{
    auto const size = m_decoratee.getSize();
    m_logger.verbose(
        std::string { "getSize: (" } + std::to_string(size.x) + ", " + std::to_string(size.y) + ")",
        { "jt", "RenderWindow" });
    return size;
}

void LoggingRenderWindowDecorator::draw(std::unique_ptr<jt::Sprite>& sprite)
{
    m_logger.verbose("draw sprite", { "jt", "RenderWindow" });
    m_decoratee.draw(sprite);
}

void LoggingRenderWindowDecorator::display()
{
    m_logger.verbose("display", { "jt", "RenderWindow" });
    m_decoratee.display();
}

Vector2f LoggingRenderWindowDecorator::getMousePosition()
{
    m_logger.verbose("getMousePosition", { "jt", "RenderWindow" });
    return m_decoratee.getMousePosition();
}

void LoggingRenderWindowDecorator::setMouseCursorVisible(bool visible)
{
    m_logger.info("setMouseCursorVisible" + std::to_string(visible), { "jt", "RenderWindow" });
    m_decoratee.setMouseCursorVisible(visible);
}
bool LoggingRenderWindowDecorator::getMouseCursorVisible() const
{
    m_logger.info("getMouseCursorVisible", { "jt", "RenderWindow" });
    return m_decoratee.getMouseCursorVisible();
}
void LoggingRenderWindowDecorator::updateGui(float elapsed)
{
    m_logger.verbose("updateGui", { "jt", "RenderWindow" });
    m_decoratee.updateGui(elapsed);
}
void LoggingRenderWindowDecorator::startRenderGui()
{
    m_logger.verbose("startRenderGui", { "jt", "RenderWindow" });
    m_decoratee.startRenderGui();
}

} // namespace jt
