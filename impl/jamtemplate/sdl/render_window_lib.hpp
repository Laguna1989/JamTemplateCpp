#ifndef JAMTEMPLATE_RENDERWINDOW_LIB_HPP
#define JAMTEMPLATE_RENDERWINDOW_LIB_HPP

#include <graphics/render_window_interface.hpp>
#include <sdl_2_include.hpp>
#include <sprite.hpp>
#include <memory>

namespace jt {
class RenderWindow : public RenderWindowInterface {
public:
    RenderWindow(unsigned int width, unsigned int height, std::string const& title);
    std::shared_ptr<jt::RenderTargetLayer> createRenderTarget() override;

    bool isOpen() const override;
    void checkForClose() override;

    jt::Vector2f getSize() const noexcept override;

    void draw(std::unique_ptr<jt::Sprite>&) override;

    void display() override;

    jt::Vector2f getMousePosition() override;

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

    bool m_renderTargetCreated { false };
};
} // namespace jt

#endif // JAMTEMPLATE_RENDERWINDOW_LIB_HPP
