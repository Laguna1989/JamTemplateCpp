#ifndef GUARD_JAMTEMPLATE_SDLHELPER_GUARD_HPP
#define GUARD_JAMTEMPLATE_SDLHELPER_GUARD_HPP

#include "Vector.hpp"
#include <SDL.h>
#include <cstddef>

namespace jt {

SDL_RendererFlip getFlipFromScale(jt::Vector2 const& scale);

void setPixel(SDL_Surface* surface, int x, int y, uint32_t pixel);

uint32_t getPixel(SDL_Surface* surface, int x, int y);

} // namespace jt
#endif
