#pragma once

#include <sdl_2_include.hpp>
#include <vector.hpp>
#include <cstddef>

namespace jt {

SDL_RendererFlip getFlipFromScale(jt::Vector2f const& scale);

void setPixel(SDL_Surface* surface, int x, int y, uint32_t pixel);

uint32_t getPixel(SDL_Surface* surface, int x, int y);

} // namespace jt
