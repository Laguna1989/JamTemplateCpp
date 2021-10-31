#ifndef GUARD_JAMTEMPLATE_RENDERWINDOW_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_RENDERWINDOW_LIB_GUARD_HPP

#include "render_window_interface.hpp"
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

    std::shared_ptr<jt::renderTarget> createRenderTarget() override;

    bool isOpen() const override;
    void checkForClose() override;

    jt::Vector2 getSize() const override;

    void draw(std::unique_ptr<jt::Sprite>&) override;

    void display() override;

    jt::Vector2 getMousePosition() override;
    void setMouseCursorVisible(bool visible) override;
    bool getMouseCursorVisible(void) const override;

private:
    std::shared_ptr<sf::RenderWindow> m_window;
    bool m_isMouseCursorVisible { true };
};
} // namespace jt

#endif
