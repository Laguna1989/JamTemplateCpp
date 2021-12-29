#include "render_window_lib.hpp"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include <SDL2/SDL.h>
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

std::shared_ptr<jt::RenderTarget> RenderWindow::createRenderTarget()
{
    auto const renderTarget
        = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(m_window.get(), -1,
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
            [](SDL_Renderer* r) { SDL_DestroyRenderer(r); });
    if (!renderTarget) {
        throw std::logic_error { "failed to create renderer." };
    }
    SDL_SetRenderDrawBlendMode(renderTarget.get(), SDL_BLENDMODE_BLEND);
    ImGui::CreateContext();
    ImGuiSDL::Initialize(
        renderTarget.get(), static_cast<int>(m_size.x), static_cast<int>(m_size.y));
    return renderTarget;
}

bool RenderWindow::isOpen() const { return m_isOpen; }

void RenderWindow::checkForClose()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
#if JT_ENABLE_WEB
        ImGui_ImplSDL2_ProcessEvent(&event);
#endif
        switch (event.type) {
        case SDL_QUIT:
            m_isOpen = false;
            break;
        }
    }
}

jt::Vector2f RenderWindow::getSize() const { return m_size; }

void RenderWindow::draw(std::unique_ptr<jt::Sprite>& spr)
{
    if (!spr) {
        throw std::invalid_argument { "cannot draw nullptr sprite" };
    }
    std::cerr << "RenderWindow::draw() not supported by SDL Renderwindow. Use the Rendertarget "
                 "directly to draw\n";
}

void RenderWindow::display()
{
    if (m_renderGui) {
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
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
    SDL_ShowCursor(SDL_ENABLE);
    m_isMouseCursorVisible = visible;
}

bool RenderWindow::getMouseCursorVisible() const { return m_isMouseCursorVisible; }

void RenderWindow::updateGui(float elapsed)
{
#if JT_ENABLE_WEB
    // actually we do not care about the initialization of the backend. However InitForMetal does
    // not do anything more than initializing the keymap, which is exactly what we want here.
    ImGui_ImplSDL2_InitForMetal(m_window.get());
#endif
    ImGuiIO& io = ImGui::GetIO();
    io.DeltaTime = elapsed;
    int mx { 0 };
    int my { 0 };
    auto const mouseState = SDL_GetMouseState(&mx, &my);
    io.MousePos = ImVec2(static_cast<float>(mx), static_cast<float>(my));
    io.MouseDown[0] = mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT);

    io.MouseWheel = 0.0f;
}

void RenderWindow::startRenderGui()
{
    ImGui::NewFrame();
    m_renderGui = true;
}

} // namespace jt
