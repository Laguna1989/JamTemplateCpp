#ifndef JAMTEMPLATE_LOGGING_RENDER_WINDOW_HPP
#define JAMTEMPLATE_LOGGING_RENDER_WINDOW_HPP

#include <graphics/render_window_interface.hpp>
#include <log/logger_interface.hpp>

namespace jt {
class LoggingRenderWindow : public RenderWindowInterface {
public:
    LoggingRenderWindow(RenderWindowInterface& decoratee, LoggerInterface& logger);
    bool isOpen() const override;
    void checkForClose() override;
    std::shared_ptr<jt::RenderTargetLayer> createRenderTarget() override;
    Vector2f getSize() const override;
    void draw(std::unique_ptr<jt::Sprite>& sprite) override;
    void display() override;
    Vector2f getMousePosition() override;
    void setMouseCursorVisible(bool visible) override;
    bool getMouseCursorVisible() const override;
    void updateGui(float elapsed) override;
    void startRenderGui() override;

    bool shouldProcessKeyboard() override;
    bool shouldProcessMouse() override;

private:
    RenderWindowInterface& m_decoratee;
    LoggerInterface& m_logger;
};
} // namespace jt

#endif // JAMTEMPLATE_LOGGING_RENDER_WINDOW_HPP
