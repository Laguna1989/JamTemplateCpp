#include "RenderWindow_lib.hpp"
#include <SDL.h>

namespace jt {

RenderWindow::RenderWindow(unsigned int width, unsigned int height, std::string const& title)
{
    m_size = jt::Vector2 { static_cast<float>(width), static_cast<float>(height) };
    m_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                               SDL_WINDOWPOS_CENTERED, width, height, 0),
        [](SDL_Window* w) { SDL_DestroyWindow(w); });
    if (!m_window) {
        throw std::logic_error { "Failed to create window." };
    }
}

std::shared_ptr<jt::renderTarget> RenderWindow::createRenderTarget()
{
    auto const renderTarget
        = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(m_window.get(), -1,
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
            [](SDL_Renderer* r) { SDL_DestroyRenderer(r); });
    if (!renderTarget) {
        throw std::logic_error { "failed to create renderer." };
    }
    SDL_SetRenderDrawBlendMode(renderTarget.get(), SDL_BLENDMODE_BLEND);
    return renderTarget;
}

bool RenderWindow::isOpen() const { return true; }

void RenderWindow::checkForClose()
{
    std::cerr << "RenderWindow::checkForClose() not supported by SDL Renderwindow. Webbuild window "
                 "cannot be closed\n";
}

jt::Vector2 RenderWindow::getSize() const { return m_size; }

void RenderWindow::draw(std::shared_ptr<jt::Sprite> /*spr*/)
{
    std::cerr << "RenderWindow::draw() not supported by SDL Renderwindow. Use the Rendertarget "
                 "directly to draw\n";
}

void RenderWindow::display()
{
    std::cerr << "RenderWindow::display() not supported by SDL Renderwindow. Use the Rendertarget "
                 "directly to draw\n";
}

jt::Vector2 RenderWindow::getMousePosition()
{
    SDL_PumpEvents();
    int mx { 0 };
    int my { 0 };
    auto const mouseState = SDL_GetMouseState(&mx, &my);
    return jt::Vector2 { static_cast<float>(mx), static_cast<float>(my) };
}

jt::Vector2 RenderWindow::getMousePositionScreen(float zoom)
{
    std::cerr << "RenderWindow::getMousepositonScreen() not supported by SDL Renderwindow.\n";
}

} // namespace jt
