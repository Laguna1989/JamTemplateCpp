#ifndef JAMTEMPLATE_SDLHELPER_HPP
#define JAMTEMPLATE_SDLHELPER_HPP

#include <vector.hpp>
#include <sdl_2_include.hpp>
#include <cstddef>

namespace jt {

SDL_RendererFlip getFlipFromScale(jt::Vector2f const& scale);

void setPixel(SDL_Surface* surface, int x, int y, uint32_t pixel);

uint32_t getPixel(SDL_Surface* surface, int x, int y);

} // namespace jt

#endif // JAMTEMPLATE_SDLHELPER_HPP
