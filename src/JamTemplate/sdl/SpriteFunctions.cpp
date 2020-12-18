#include "SpriteFunctions.hpp"
#include "Color.hpp"
#include "MathHelper.hpp"
#include "SDLHelper.hpp"
#include <cmath>

namespace jt {

namespace SpriteFunctions {

std::shared_ptr<SDL_Texture> makeButtonImage(std::shared_ptr<jt::renderTarget> rt, unsigned int w,
    unsigned int h, jt::Color midColor, jt::Color darkColor, jt::Color brightColor)
{
    std::shared_ptr<SDL_Surface> image
        = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurface(0, w * 3, h, 32, 0, 0, 0, 0),
            [](SDL_Surface* s) { SDL_FreeSurface(s); });

    auto const mid = SDL_MapRGBA(image->format, midColor.r(), midColor.g(), midColor.b(), 255U);
    auto const dark = SDL_MapRGBA(image->format, darkColor.r(), darkColor.g(), darkColor.b(), 255U);
    auto const bright
        = SDL_MapRGBA(image->format, brightColor.r(), brightColor.g(), brightColor.b(), 255U);

    for (auto i = 0U; i != w * 3; ++i) {
        for (auto j = 0U; j != h; ++j) {
            jt::setPixel(image.get(), i, j, mid);
        }
    }

    for (unsigned int i = 0U; i != w; ++i) {
        setPixel(image.get(), i, 0, bright);
        setPixel(image.get(), i, h - 1, dark);
        setPixel(image.get(), 2 * w + i, 0, dark);
        setPixel(image.get(), 2 * w + i, h - 1, bright);
    }

    for (unsigned int j = 0U; j != h; ++j) {
        setPixel(image.get(), 0, j, bright);
        setPixel(image.get(), w - 1, j, dark);
        setPixel(image.get(), 2 * w, j, dark);
        setPixel(image.get(), 3 * w - 1, j, bright);
    }
    return std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(rt.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
}

std::shared_ptr<SDL_Texture> makeGlowImage(
    std::shared_ptr<jt::renderTarget> rt, float r, std::uint8_t max)
{
    unsigned int const s = static_cast<unsigned int>(r + 0.5f * 2);
    std::shared_ptr<SDL_Surface> image = std::shared_ptr<SDL_Surface>(
        SDL_CreateRGBSurfaceWithFormat(0, s, s, 32, SDL_PIXELFORMAT_RGBA32),
        [](SDL_Surface* s) { SDL_FreeSurface(s); });

    float const c = r / 2;

    for (auto i = 0U; i != s; ++i) {
        for (auto j = 0U; j != s; ++j) {
            auto const dx = i - c;
            auto const dy = j - c;

            auto const sqr = std::sqrt(dx * dx + dy * dy);
            auto const sqrNorm = 1.0f - MathHelper::clamp(sqr / s * 2.0f, 0.0f, 1.0f);
            float const v = std::pow(sqrNorm, 2.0f) * max;

            jt::setPixel(image.get(), i, j,
                SDL_MapRGBA(image->format, 255U, 255U, 255U, static_cast<uint8_t>(v)));
        }
    }
    return std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(rt.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
}

std::shared_ptr<SDL_Texture> makeVignetteImage(
    std::shared_ptr<jt::renderTarget> rt, unsigned int w, unsigned int h)
{
    std::shared_ptr<SDL_Surface> image = std::shared_ptr<SDL_Surface>(
        SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32),
        [](SDL_Surface* s) { SDL_FreeSurface(s); });
    // SDL_SetAlpha(image.get(), SDL_SRCALPHA, 255);
    SDL_SetSurfaceBlendMode(image.get(), SDL_BLENDMODE_BLEND);
    float const cx = w / 2.0f;
    float const cy = h / 2.0f;
    for (auto i = 0U; i != w; ++i) {
        for (auto j = 0U; j != h; ++j) {
            auto const dx = i - cx;
            auto const dy = j - cy;
            auto const sqr = std::sqrt(dx * dx + dy * dy);
            auto const sqrNorm = MathHelper::clamp(sqr / (cx + cy) / 1.5f * 2.0f, 0.0f, 1.0f);
            uint8_t const v = static_cast<uint8_t>(std::pow(sqrNorm, 2.0f) * 255);
            // std::cout << static_cast<int>(v) << "\n";
            jt::setPixel(image.get(), i, j, SDL_MapRGBA(image->format, 0U, 0U, 0U, v));
        }
    }

    std::shared_ptr<SDL_Texture> t(SDL_CreateTextureFromSurface(rt.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
    SDL_SetTextureBlendMode(t.get(), SDL_BLENDMODE_BLEND);
    return t;
}

std::shared_ptr<SDL_Texture> makeRect(
    std::shared_ptr<jt::renderTarget> rt, unsigned int w, unsigned int h)
{
    std::shared_ptr<SDL_Surface> image = std::shared_ptr<SDL_Surface>(
        SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32),
        [](SDL_Surface* s) { SDL_FreeSurface(s); });
    // SDL_SetAlpha(image.get(), SDL_SRCALPHA, 255);
    SDL_SetSurfaceBlendMode(image.get(), SDL_BLENDMODE_BLEND);
    SDL_FillRect(image.get(), NULL, SDL_MapRGBA(image->format, 255, 255, 255, 255));

    std::shared_ptr<SDL_Texture> t(SDL_CreateTextureFromSurface(rt.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
    SDL_SetTextureBlendMode(t.get(), SDL_BLENDMODE_BLEND);
    return t;
}

} // namespace SpriteFunctions
} // namespace jt
