#ifndef JAMTEMPLATE_SDLHELPER_GUARD_HPP
#define JAMTEMPLATE_SDLHELPER_GUARD_HPP
#include "vector.hpp"
#include <SDL.h>

namespace jt {

SDL_RendererFlip getFlipFromScale(jt::vector2 const& scale);
}
#endif