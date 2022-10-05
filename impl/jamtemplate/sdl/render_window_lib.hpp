﻿#ifndef JAMTEMPLATE_RENDERWINDOW_LIB_HPP
#define JAMTEMPLATE_RENDERWINDOW_LIB_HPP

#include <graphics/render_window_interface.hpp>
#include <sprite.hpp>
#include <SDL2/SDL.h>
#include <memory>

namespace jt {
class RenderWindow : public RenderWindowInterface {
public:
    RenderWindow(unsigned int width, unsigned int height, std::string const& title);
    virtual std::shared_ptr<jt::RenderTargetLayer> createRenderTarget() override;

    virtual bool isOpen() const override;
    virtual void checkForClose() override;

    virtual jt::Vector2f getSize() const override;

    virtual void draw(std::unique_ptr<jt::Sprite>&) override;

    virtual void display() override;

    virtual jt::Vector2f getMousePosition() override;

    void setMouseCursorVisible(bool visible) override;
    bool getMouseCursorVisible() const override;

    void startRenderGui() override;
    void updateGui(float elapsed) override;

    bool shouldProcessKeyboard() override;
    bool shouldProcessMouse() override;

private:
    std::shared_ptr<SDL_Window> m_window;
    jt::Vector2f m_size;
    bool m_isMouseCursorVisible { true };
    bool m_isOpen { true };
    bool m_renderGui { false };
};
} // namespace jt

#endif // JAMTEMPLATE_RENDERWINDOW_LIB_HPP
