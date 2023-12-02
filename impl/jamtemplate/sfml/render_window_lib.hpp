#ifndef JAMTEMPLATE_RENDERWINDOW_LIB_HPP
#define JAMTEMPLATE_RENDERWINDOW_LIB_HPP

#include <SFML/Graphics.hpp>
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

    // no copy, no move
    RenderWindow(RenderWindow const&) = delete;
    RenderWindow(RenderWindow&&) = delete;
    RenderWindow& operator=(RenderWindow const&) = delete;
    RenderWindow& operator=(RenderWindow&&) = delete;
    ~RenderWindow() override;

    std::shared_ptr<jt::RenderTargetLayer> createRenderTarget() override;

    bool isOpen() const override;
    void checkForClose() override;

    jt::Vector2f getSize() const noexcept override;

    void draw(std::unique_ptr<jt::Sprite>&) override;
    void startRenderGui() override;
    void updateGui(float elapsed) override;
    void display() override;

    jt::Vector2f getMousePosition() override;
    void setMouseCursorVisible(bool visible) override;
    bool getMouseCursorVisible() const noexcept override;

    bool shouldProcessKeyboard() override;
    bool shouldProcessMouse() override;

private:
    std::shared_ptr<sf::RenderWindow> m_window;
    bool m_isMouseCursorVisible { true };
    bool m_renderGui { false };

    bool m_hasBeenUpdatedAlready { false };

    jt::Vector2f m_size { 0.0f, 0.0f };
};
} // namespace jt

#endif
