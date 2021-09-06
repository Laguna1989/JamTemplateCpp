#ifndef GUARD_JAMTEMPLATE_RENDERWINDOW_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_RENDERWINDOW_LIB_GUARD_HPP

#include "render_window_interface.hpp"
#include "sprite.hpp"
#include <SDL.h>
#include <memory>

namespace jt {
class RenderWindow : public RenderWindowInterface {
public:
    RenderWindow(unsigned int width, unsigned int height, std::string const& title);
    virtual std::shared_ptr<jt::renderTarget> createRenderTarget() override;

    virtual bool isOpen() const override;
    virtual void checkForClose() override;

    virtual jt::Vector2 getSize() const override;

    virtual void draw(std::shared_ptr<jt::Sprite>) override;

    virtual void display() override;

    virtual jt::Vector2 getMousePosition() override;
    virtual jt::Vector2 getMousePositionScreen(float zoom) override;

    void setMouseCursorVisible(bool visible) override;
    bool getMouseCursorVisible() const override;

private:
    std::shared_ptr<SDL_Window> m_window;
    jt::Vector2 m_size;
    bool m_isMouseCursorVisible{true};
};
} // namespace jt

#endif
