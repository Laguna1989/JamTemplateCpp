#ifndef GUARD_JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD

#include "color.hpp"
#include "render_target.hpp"
#include <SDL2/SDL.h>
#include <memory>

namespace jt {
namespace SpriteFunctions {

std::shared_ptr<SDL_Texture> makeButtonImage(std::shared_ptr<jt::RenderTarget> renderTarget,
    unsigned int w, unsigned int h, jt::Color midColor = jt::Color { 200, 200, 200 },
    jt::Color darkColor = jt::Color { 100, 100, 100 },
    jt::Color brightColor = jt::Color { 255, 255, 255 });

std::shared_ptr<SDL_Texture> makeBlankImage(
    std::shared_ptr<jt::RenderTarget> renderTarget, unsigned int w, unsigned int h);

std::shared_ptr<SDL_Texture> makeGlowImage(
    std::shared_ptr<jt::RenderTarget> renderTarget, float r, std::uint8_t max = 255);

std::shared_ptr<SDL_Texture> makeVignetteImage(
    std::shared_ptr<jt::RenderTarget> renderTarget, unsigned int w, unsigned int h);

std::shared_ptr<SDL_Texture> makeRect(
    std::shared_ptr<jt::RenderTarget> renderTarget, unsigned int w, unsigned int h);

std::shared_ptr<SDL_Texture> makeCircle(std::shared_ptr<jt::RenderTarget> renderTarget, float r);

} // namespace SpriteFunctions

} // namespace jt

#endif
