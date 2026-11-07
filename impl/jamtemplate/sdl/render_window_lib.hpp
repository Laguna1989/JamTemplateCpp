#pragma once

#include <graphics/render_window_interface.hpp>
#include <sdl_2_include.hpp>
#include <sprite.hpp>
#include <memory>

namespace jt {
class RenderWindow : public RenderWindowInterface {
public:
    RenderWindow(unsigned int width, unsigned int height, std::string const& title);
    ~RenderWindow() override;

    RenderWindow(RenderWindow const&) = delete;
    RenderWindow(RenderWindow&&) = delete;
    RenderWindow& operator=(RenderWindow const&) = delete;
    RenderWindow& operator=(RenderWindow&&) = delete;

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
    void shutdownGui();

    std::shared_ptr<SDL_Window> m_window;
    // Kept alive by the window so the imgui renderer backend can be shut down before the renderer
    // is destroyed. Declared after m_window so it is destroyed before the window.
    std::shared_ptr<SDL_Renderer> m_renderer;
    jt::Vector2f m_size;
    bool m_isMouseCursorVisible { true };
    bool m_isOpen { true };
    bool m_renderGui { false };

    bool m_renderTargetCreated { false };
};
} // namespace jt
