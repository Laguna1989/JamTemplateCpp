#include "sdl_helper.hpp"

namespace jt {

SDL_RendererFlip getFlipFromScale(jt::Vector2f const& scale)
{
    auto flip = SDL_FLIP_NONE;
    if (scale.x < 0 && scale.y < 0) {
        flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    } else if (scale.x < 0 && scale.y >= 0) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (scale.x >= 0 && scale.y < 0) {
        flip = SDL_FLIP_VERTICAL;
    }
    return flip;
}

void setPixel(SDL_Surface* surface, int x, int y, uint32_t pixel)
{
    uint8_t* target_pixel = static_cast<uint8_t*>(surface->pixels) + y * surface->pitch + x * 4;
    *(uint32_t*)target_pixel = pixel;
}

uint32_t getPixel(SDL_Surface* surface, int x, int y)
{
    int const bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    uint8_t* p = static_cast<uint8_t*>(surface->pixels) + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(uint16_t*)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            return p[0] << 16 | p[1] << 8 | p[2];
        } else {
            return p[0] | p[1] << 8 | p[2] << 16;
        }
        break;

    case 4:
        return *(uint32_t*)p;
        break;

    default:
        return 0; /* shouldn't happen, but avoids warnings */
    }
}

} // namespace jt
