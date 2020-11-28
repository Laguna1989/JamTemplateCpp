#include "SDLHelper.hpp"

namespace jt {

SDL_RendererFlip getFlipFromScale(jt::vector2 const& scale)
{
    auto flip = SDL_FLIP_NONE;
    if (scale.x() < 0 && scale.y() < 0) {
        flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    } else if (scale.x() < 0 && scale.y() >= 0) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (scale.x() >= 0 && scale.y() < 0) {
        flip = SDL_FLIP_VERTICAL;
    }
    return flip;
}

} // namespace jt