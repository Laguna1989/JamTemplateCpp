#ifndef JAMTEMPLATE_RENDERWINDOW_LIB_HPP
#define JAMTEMPLATE_RENDERWINDOW_LIB_HPP

#include <graphics/render_window_interface.hpp>
#include <memory>

namespace sf {
class RenderWindow;
class View;
} // namespace sf

namespace jt {
class RenderWindow : public RenderWindowInterface {
public:
    /// Constructor
    /// \param width width of the window in pixel
    /// \param height height of the window in pixel
    /// \param title title of the window
    RenderWindow(unsigned int width, unsigned int height, std::string const& title);

    // no copy, only move
    RenderWindow(const RenderWindow&) = delete;
    RenderWindow(RenderWindow&&) = default;
    RenderWindow& operator=(const RenderWindow&) = delete;
    RenderWindow& operator=(RenderWindow&&) = default;
    ~RenderWindow() = default;

    std::shared_ptr<jt::RenderTargetLayer> createRenderTarget() override;

    bool isOpen() const override;
    void checkForClose() override;

    jt::Vector2f getSize() const override;

    void draw(std::unique_ptr<jt::Sprite>&) override;
    void startRenderGui() override;
    void updateGui(float elapsed) override;
    void display() override;

    jt::Vector2f getMousePosition() override;
    void setMouseCursorVisible(bool visible) override;
    bool getMouseCursorVisible(void) const override;

    bool shouldProcessKeyboard() override;
    bool shouldProcessMouse() override;

private:
    std::shared_ptr<sf::RenderWindow> m_window;
    bool m_isMouseCursorVisible { true };
    bool m_renderGui { false };

    bool m_hasBeenUpdatedAlready { false };
};
} // namespace jt

#endif
