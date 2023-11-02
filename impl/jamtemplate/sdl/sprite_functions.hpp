#ifndef JAMTEMPLATE_SPRITEFUNCTIONS_HPP
#define JAMTEMPLATE_SPRITEFUNCTIONS_HPP

#include <color/color.hpp>
#include <render_target_layer.hpp>
#include <sdl_2_include.hpp>
#include <memory>

namespace jt {
namespace SpriteFunctions {

std::shared_ptr<SDL_Texture> makeButtonImage(std::shared_ptr<jt::RenderTargetLayer> renderTarget,
    unsigned int w, unsigned int h, jt::Color midColor = jt::Color { 200, 200, 200 },
    jt::Color darkColor = jt::Color { 100, 100, 100 },
    jt::Color brightColor = jt::Color { 255, 255, 255 });

std::shared_ptr<SDL_Texture> makeBlankImage(
    std::shared_ptr<jt::RenderTargetLayer> renderTarget, unsigned int w, unsigned int h);

std::shared_ptr<SDL_Texture> makeGlowImage(
    std::shared_ptr<jt::RenderTargetLayer> renderTarget, float r, std::uint8_t max = 255);

std::shared_ptr<SDL_Texture> makeVignetteImage(
    std::shared_ptr<jt::RenderTargetLayer> renderTarget, unsigned int w, unsigned int h);

std::shared_ptr<SDL_Texture> makeRect(
    std::shared_ptr<jt::RenderTargetLayer> renderTarget, unsigned int w, unsigned int h);

std::shared_ptr<SDL_Texture> makeCircle(
    std::shared_ptr<jt::RenderTargetLayer> renderTarget, float r);

std::shared_ptr<SDL_Texture> makeRing(
    std::shared_ptr<jt::RenderTargetLayer> renderTarget, unsigned int w);

} // namespace SpriteFunctions

} // namespace jt

#endif
