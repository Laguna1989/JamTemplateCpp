#ifndef GUARD_JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD

#include "color.hpp"
#include "rendertarget.hpp"
#include <SDL.h>
#include <memory>

namespace jt {
namespace SpriteFunctions {

std::shared_ptr<SDL_Texture> makeButtonImage(std::shared_ptr<jt::renderTarget> rt, unsigned int w,
    unsigned int h, jt::color midColor = jt::color { 200, 200, 200 },
    jt::color darkColor = jt::color { 100, 100, 100 },
    jt::color brightColor = jt::color { 255, 255, 255 });

std::shared_ptr<SDL_Texture> makeGlowImage(
    std::shared_ptr<jt::renderTarget> rt, float r, std::uint8_t max = 255);

std::shared_ptr<SDL_Texture> makeVignetteImage(
    std::shared_ptr<jt::renderTarget> rt, unsigned int w, unsigned int h);

std::shared_ptr<SDL_Texture> makeRect(
    std::shared_ptr<jt::renderTarget> rt, unsigned int w, unsigned int h);

} // namespace SpriteFunctions

} // namespace jt

#endif
