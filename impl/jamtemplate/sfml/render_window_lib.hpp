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
    RenderWindow(unsigned int width, unsigned int height, std::string const& title);

    std::shared_ptr<jt::renderTarget> createRenderTarget() override;

    bool isOpen() const override;
    void checkForClose() override;

    jt::Vector2 getSize() const override;

    void draw(std::unique_ptr<jt::Sprite>) override;

    void display() override;

    jt::Vector2 getMousePosition() override;
    jt::Vector2 getMousePositionScreen(float zoom) override;
    void setMouseCursorVisible(bool visible) override;
    bool getMouseCursorVisible(void) const override;

    // do not use/write s_view manually from gameplay code. Should only be set once in Game.cpp.
    static std::weak_ptr<sf::View> s_view;

private:
    std::shared_ptr<sf::RenderWindow> m_window;
    bool m_isMouseCursorVisible { true };
};
} // namespace jt

#endif
