#include "sprite_functions.hpp"
#include "math_helper.hpp"
#include "random/random.hpp"
#include "sdl_helper.hpp"
#include <cmath>

namespace jt {

namespace SpriteFunctions {

std::shared_ptr<SDL_Texture> makeButtonImage(std::shared_ptr<jt::RenderTarget> renderTarget,
    unsigned int w, unsigned int h, jt::Color midColor, jt::Color darkColor, jt::Color brightColor)
{
    auto const wAsInt = static_cast<int>(w);
    auto const hAsInt = static_cast<int>(h);
    std::shared_ptr<SDL_Surface> image
        = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurface(0, wAsInt * 3, hAsInt, 32, 0, 0, 0, 0),
            [](SDL_Surface* s) { SDL_FreeSurface(s); });

    auto const max = std::numeric_limits<std::uint8_t>::max();
    auto const mid = SDL_MapRGBA(image->format, midColor.r, midColor.g, midColor.b, max);
    auto const dark = SDL_MapRGBA(image->format, darkColor.r, darkColor.g, darkColor.b, max);
    auto const bright
        = SDL_MapRGBA(image->format, brightColor.r, brightColor.g, brightColor.b, max);

    for (auto i = 0U; i != w * 3; ++i) {
        for (auto j = 0U; j != h; ++j) {
            jt::setPixel(image.get(), i, j, mid);
        }
    }

    for (int i = 0; i != wAsInt; ++i) {
        setPixel(image.get(), i, 0, bright);
        setPixel(image.get(), i, hAsInt - 1, dark);
        setPixel(image.get(), 2 * wAsInt + i, 0, dark);
        setPixel(image.get(), 2 * wAsInt + i, hAsInt - 1, bright);
    }

    for (int j = 0; j != hAsInt; ++j) {
        setPixel(image.get(), 0, j, bright);
        setPixel(image.get(), wAsInt - 1, j, dark);
        setPixel(image.get(), 2 * wAsInt, j, dark);
        setPixel(image.get(), 3 * wAsInt - 1, j, bright);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    return std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderTarget.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
}

std::shared_ptr<SDL_Texture> makeBlankImage(
    std::shared_ptr<jt::RenderTarget> renderTarget, unsigned int w, unsigned int h)
{
    std::shared_ptr<SDL_Surface> image = std::shared_ptr<SDL_Surface>(
        SDL_CreateRGBSurface(0, static_cast<int>(w), static_cast<int>(h), 32, 0, 0, 0, 0),
        [](SDL_Surface* s) { SDL_FreeSurface(s); });

    for (auto i = 0U; i != w; ++i) {
        for (auto j = 0U; j != h; ++j) {
            auto const max = std::numeric_limits<std::uint8_t>::max();
            auto const col = SDL_MapRGBA(image->format, max, max, max, max);
            jt::setPixel(image.get(), i, j, col);
        }
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    return std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderTarget.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
}

std::shared_ptr<SDL_Texture> makeGlowImage(
    std::shared_ptr<jt::RenderTarget> renderTarget, float r, std::uint8_t max)
{
    auto const s = static_cast<unsigned int>(r + 0.5f * 2);
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
            float const v = std::pow(sqrNorm, 2.0f) * static_cast<float>(max);

            auto const max = std::numeric_limits<std::uint8_t>::max();
            jt::setPixel(image.get(), i, j,
                SDL_MapRGBA(image->format, max, max, max, static_cast<uint8_t>(v)));
        }
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    return std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderTarget.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
}

std::shared_ptr<SDL_Texture> makeVignetteImage(
    std::shared_ptr<jt::RenderTarget> renderTarget, unsigned int w, unsigned int h)
{
    std::shared_ptr<SDL_Surface> image
        = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurfaceWithFormat(0, static_cast<int>(w),
                                           static_cast<int>(h), 32, SDL_PIXELFORMAT_RGBA32),
            [](SDL_Surface* s) { SDL_FreeSurface(s); });
    // SDL_SetAlpha(image.get(), SDL_SRCALPHA, 255);
    SDL_SetSurfaceBlendMode(image.get(), SDL_BLENDMODE_BLEND);
    float const cx = static_cast<float>(w) / 2.0f;
    float const cy = static_cast<float>(h) / 2.0f;
    for (auto i = 0U; i != w; ++i) {
        for (auto j = 0U; j != h; ++j) {
            auto const dx = i - cx;
            auto const dy = j - cy;
            auto const sqr = std::sqrt(dx * dx + dy * dy);
            auto const sqrNorm = MathHelper::clamp(sqr / (cx + cy) / 1.5f * 2.0f, 0.0f, 1.0f);
            auto const v
                = static_cast<uint8_t>(std::pow(sqrNorm, 2.0f) * 235 + jt::Random::getInt(0, 20));
            jt::setPixel(image.get(), i, j, SDL_MapRGBA(image->format, 0U, 0U, 0U, v));
        }
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    std::shared_ptr<SDL_Texture> t(SDL_CreateTextureFromSurface(renderTarget.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
    SDL_SetTextureBlendMode(t.get(), SDL_BLENDMODE_BLEND);
    return t;
}

std::shared_ptr<SDL_Texture> makeRect(
    std::shared_ptr<jt::RenderTarget> renderTarget, unsigned int w, unsigned int h)
{
    std::shared_ptr<SDL_Surface> image
        = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurfaceWithFormat(0, static_cast<int>(w),
                                           static_cast<int>(h), 32, SDL_PIXELFORMAT_RGBA32),
            [](SDL_Surface* s) { SDL_FreeSurface(s); });
    // SDL_SetAlpha(image.get(), SDL_SRCALPHA, 255);
    SDL_SetSurfaceBlendMode(image.get(), SDL_BLENDMODE_BLEND);
    auto const max = std::numeric_limits<std::uint8_t>::max();
    SDL_FillRect(image.get(), nullptr, SDL_MapRGBA(image->format, max, max, max, max));

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    std::shared_ptr<SDL_Texture> t(SDL_CreateTextureFromSurface(renderTarget.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
    SDL_SetTextureBlendMode(t.get(), SDL_BLENDMODE_BLEND);
    return t;
}

std::shared_ptr<SDL_Texture> makeCircle(std::shared_ptr<jt::RenderTarget> renderTarget, float r)
{
    auto const s = static_cast<unsigned int>((r + 0.5f) * 2);
    std::shared_ptr<SDL_Surface> image = std::shared_ptr<SDL_Surface>(
        SDL_CreateRGBSurfaceWithFormat(0, s, s, 32, SDL_PIXELFORMAT_RGBA32),
        [](SDL_Surface* s) { SDL_FreeSurface(s); });

    float const c = r;

    for (auto i = 0U; i != s; ++i) {
        for (auto j = 0U; j != s; ++j) {
            auto const dx = i - c;
            auto const dy = j - c;

            auto const sqr = std::sqrt(dx * dx + dy * dy);

            float const v = (sqr < r) ? 255 : 0;

            auto const max = std::numeric_limits<std::uint8_t>::max();
            jt::setPixel(image.get(), i, j,
                SDL_MapRGBA(image->format, max, max, max, static_cast<uint8_t>(v)));
        }
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    return std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderTarget.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
}

} // namespace SpriteFunctions
} // namespace jt
