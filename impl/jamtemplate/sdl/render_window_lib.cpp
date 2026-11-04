#include "render_window_lib.hpp"
#include <sdl_2_include.hpp>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <iostream>

namespace jt {

RenderWindow::RenderWindow(unsigned int width, unsigned int height, std::string const& title)
{
    m_size = jt::Vector2f { static_cast<float>(width), static_cast<float>(height) };
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    m_window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            static_cast<int>(width), static_cast<int>(height), 0),
        [](SDL_Window* w) { SDL_DestroyWindow(w); });
    if (!m_window) {
        throw std::logic_error { "Failed to create window." };
    }
}

std::shared_ptr<jt::RenderTargetLayer> RenderWindow::createRenderTarget()
{
    auto const renderTarget
        = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(m_window.get(), -1,
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
            [](SDL_Renderer* r) { SDL_DestroyRenderer(r); });
    if (!renderTarget) {
        throw std::logic_error { "failed to create renderer." };
    }
    SDL_SetRenderDrawBlendMode(renderTarget.get(), SDL_BLENDMODE_BLEND);

    if (m_renderTargetCreated) {
        shutdownGui();
    }
    m_renderer = renderTarget;
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForSDLRenderer(m_window.get(), m_renderer.get());
    ImGui_ImplSDLRenderer2_Init(m_renderer.get());
    m_renderTargetCreated = true;
    return renderTarget;
}

RenderWindow::~RenderWindow()
{
    if (m_renderTargetCreated) {
        shutdownGui();
    }
}

void RenderWindow::shutdownGui()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    m_renderTargetCreated = false;
}

bool RenderWindow::isOpen() const { return m_isOpen; }

void RenderWindow::checkForClose()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (m_renderTargetCreated) {
            ImGui_ImplSDL2_ProcessEvent(&event);
        }
        switch (event.type) {
        case SDL_QUIT:
            m_isOpen = false;
            break;
        }
    }
}

jt::Vector2f RenderWindow::getSize() const noexcept { return m_size; }

void RenderWindow::draw(std::unique_ptr<jt::Sprite>& spr)
{
    if (!spr) [[unlikely]] {
        throw std::invalid_argument { "cannot draw nullptr sprite" };
    }
    std::cerr << "RenderWindow::draw() not supported by SDL Renderwindow. Use the Rendertarget "
                 "directly to draw\n";
}

void RenderWindow::display()
{
    if (!m_renderTargetCreated) [[unlikely]] {
        return;
    }
    if (m_renderGui) {
        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer.get());
    }
    m_renderGui = false;
}

jt::Vector2f RenderWindow::getMousePosition()
{
    SDL_PumpEvents();
    int mx { 0 };
    int my { 0 };
    auto const mouseState = SDL_GetMouseState(&mx, &my);
    (void)mouseState;
    return jt::Vector2f { static_cast<float>(mx), static_cast<float>(my) };
}

void RenderWindow::setMouseCursorVisible(bool visible)
{
    if (visible) {
        SDL_ShowCursor(SDL_ENABLE);
    } else {
        SDL_ShowCursor(SDL_DISABLE);
    }

    m_isMouseCursorVisible = visible;
}

bool RenderWindow::getMouseCursorVisible() const { return m_isMouseCursorVisible; }

void RenderWindow::updateGui(float elapsed)
{
    if (!m_renderTargetCreated) [[unlikely]] {
        return;
    }
    // The backends feed display size, mouse and keyboard state from the processed SDL events.
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    if (elapsed > 0.0f) {
        ImGui::GetIO().DeltaTime = elapsed;
    }
}

void RenderWindow::startRenderGui()
{
    if (!m_renderTargetCreated) [[unlikely]] {
        return;
    }
    ImGui::NewFrame();
    m_renderGui = true;
}

bool RenderWindow::shouldProcessKeyboard()
{
    if (!m_renderTargetCreated) [[unlikely]] {
        return true;
    }
    return !ImGui::GetIO().WantCaptureKeyboard;
}

bool RenderWindow::shouldProcessMouse()
{
    if (!m_renderTargetCreated) [[unlikely]] {
        return true;
    }
    return !ImGui::GetIO().WantCaptureMouse;
}

} // namespace jt
