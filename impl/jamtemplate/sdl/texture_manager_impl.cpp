#include "texture_manager_impl.hpp"
#include "sdl_helper.hpp"
#include "sprite_functions.hpp"
#include "strutils.hpp"
#include <SDL_image.h>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>

namespace jt {

namespace {

std::shared_ptr<SDL_Texture> createButtonImage(
    std::vector<std::string> const& ssv, std::shared_ptr<jt::RenderTarget> renderTarget)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument { "create button image: vector does not contain 3 elements." };
    }
    std::size_t count { 0 };
    std::int64_t const w = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size()) {
        throw std::invalid_argument { "invalid button size string" };
    }
    std::int64_t const h = std::stol(ssv.at(2), &count);
    if (count != ssv.at(2).size()) {
        throw std::invalid_argument { "invalid button size string" };
    }
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument { "invalid button size" };
    }

    return jt::SpriteFunctions::makeButtonImage(renderTarget, w, h);
}

std::shared_ptr<SDL_Texture> createBlankImage(
    std::vector<std::string> const& ssv, std::shared_ptr<jt::RenderTarget> renderTarget)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument { "create button image: vector does not contain 3 elements." };
    }
    std::size_t count { 0 };
    std::int64_t const w = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size()) {
        throw std::invalid_argument { "invalid image size string" };
    }
    std::int64_t const h = std::stol(ssv.at(2), &count);
    if (count != ssv.at(2).size()) {
        throw std::invalid_argument { "invalid image size string" };
    }
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument { "invalid image size" };
    }

    return SpriteFunctions::makeBlankImage(
        renderTarget, static_cast<unsigned int>(w), static_cast<unsigned int>(h));
}

std::shared_ptr<SDL_Texture> createGlowImage(
    std::vector<std::string> const& ssv, std::shared_ptr<jt::RenderTarget> renderTarget)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument { "create glow image: vector does not contain 2 elements." };
    }
    std::size_t count { 0 };
    auto const glow_size = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size() || glow_size <= std::numeric_limits<uint8_t>::min()) {
        throw std::invalid_argument { "invalid glow size" };
    }
    auto const max = std::stol(ssv.at(2), &count);

    if (count != ssv.at(2).size() || max <= std::numeric_limits<uint8_t>::min()
        || max > std::numeric_limits<uint8_t>::max()) {
        throw std::invalid_argument { "invalid glowmax" };
    }
    return SpriteFunctions::makeGlowImage(
        renderTarget, static_cast<float>(glow_size), static_cast<uint8_t>(max));
}

std::shared_ptr<SDL_Texture> createVignetteImage(
    std::vector<std::string> const& ssv, std::shared_ptr<jt::RenderTarget> renderTarget)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument {
            "create vignette image: vector does not contain 2 elements."
        };
    }
    std::size_t count { 0 };
    auto const w = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size() || w <= 0) {
        throw std::invalid_argument { "invalid vignette w" };
    }
    auto const h = std::stol(ssv.at(2), &count);
    if (count != ssv.at(2).size() || h <= 0) {
        std::cout << "invalid vignette h\n";
        throw std::invalid_argument { "invalid vignette h" };
    }
    return SpriteFunctions::makeVignetteImage(renderTarget, w, h);
}

std::shared_ptr<SDL_Texture> createRectImage(
    std::vector<std::string> const& ssv, std::shared_ptr<jt::RenderTarget> renderTarget)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument { "create rect image: vector does not contain 2 elements." };
    }
    std::size_t count { 0 };
    auto const w = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size() || w <= 0) {
        throw std::invalid_argument { "invalid rect w" };
    }
    auto const h = std::stol(ssv.at(2), &count);
    if (count != ssv.at(2).size() || h <= 0) {
        std::cout << "invalid rect h\n";
        throw std::invalid_argument { "invalid rect h" };
    }
    return SpriteFunctions::makeRect(renderTarget, w, h);
}

std::shared_ptr<SDL_Texture> createCircleImage(
    std::vector<std::string> const& ssv, std::shared_ptr<jt::RenderTarget> renderTarget)
{
    if (ssv.size() != 2) {
        throw std::invalid_argument { "create circle image: vector does not contain 1 elements." };
    }
    std::size_t count { 0 };
    auto const radius = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size() || radius <= std::numeric_limits<uint8_t>::min()) {
        throw std::invalid_argument { "invalid circle radius" };
    }
    return SpriteFunctions::makeCircle(renderTarget, static_cast<float>(radius));
}

std::shared_ptr<SDL_Texture> createFlashImage(
    std::string const& str, std::shared_ptr<jt::RenderTarget> renderTarget)
{
    auto image = std::shared_ptr<SDL_Surface>(
        IMG_Load(str.c_str()), [](SDL_Surface* s) { SDL_FreeSurface(s); });
    if (!image) {
        return nullptr;
    }
    int const w = image->w;
    int const h = image->h;

    auto const white = SDL_MapRGBA(image->format, 255U, 255U, 255U, 255U);

    for (int x = 0; x != w; ++x) {
        for (int y = 0; y != h; ++y) {

            uint8_t r = 0u;
            uint8_t g = 0u;
            uint8_t b = 0u;
            uint8_t a = 0u;
            SDL_GetRGBA(jt::getPixel(image.get(), x, y), image->format, &r, &g, &b, &a);
            if (a != 0) {
                jt::setPixel(image.get(), x, y, white);
            }
        }
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    return std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderTarget.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
}

std::shared_ptr<SDL_Texture> loadTextureFromDisk(
    std::string const& str, std::shared_ptr<jt::RenderTarget> renderTarget)
{
    if (renderTarget == nullptr) {
        throw std::logic_error { "rendertarget is null in loadTextureFromDisk" };
    }
    auto t = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderTarget.get(), str.c_str()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });

    if (t == nullptr) {
        throw std::invalid_argument { "invalid filename, cannot load texture from '" + str + "'" };
    }
    return t;
}
} // namespace

TextureManagerImpl::TextureManagerImpl(std::shared_ptr<jt::RenderTarget> renderer)
{
    m_renderer = renderer;
}

std::shared_ptr<SDL_Texture> TextureManagerImpl::get(std::string const& str)
{
    if (str.empty()) {
        std::cout << "TextureManager get: string must not be empty" << std::endl;
        throw std::invalid_argument { "TextureManager get: string must not be empty" };
    }
    if (m_renderer.expired()) {
        std::cout << "renderer not available for TextureManager::get()" << std::endl;
        throw std::logic_error { "renderer not available for TextureManager::get()" };
    }

    // check if texture is already stored in texture manager
    if (!containsTexture(str)) {
        // normal filenames do not start with a '#'
        if (str.at(0) != '#') {
            m_textures[str] = loadTextureFromDisk(str, m_renderer.lock());

            // create Flash Image
            m_textures[getFlashName(str)] = createFlashImage(str, m_renderer.lock());
        } else // special type of images
        {
            auto ssv = strutil::split(str.substr(1U), '#');
            if (ssv.at(0) == "b") {
                m_textures[str] = createButtonImage(ssv, m_renderer.lock());
            } else if (ssv.at(0) == "f") {
                m_textures[str] = createBlankImage(ssv, m_renderer.lock());
            } else if (ssv.at(0) == "g") {
                m_textures[str] = createGlowImage(ssv, m_renderer.lock());
            } else if (ssv.at(0) == "v") {
                m_textures[str] = createVignetteImage(ssv, m_renderer.lock());
            } else if (ssv.at(0) == "x") {
                return createRectImage(ssv, m_renderer.lock());
            } else if (ssv.at(0) == "c") {
                return createCircleImage(ssv, m_renderer.lock());
            } else {
                throw std::invalid_argument("ERROR: cannot get texture with name " + str);
            }
            m_textures[getFlashName(str)] = m_textures[str];
        }
    }

    return m_textures[str];
}

std::string TextureManagerImpl::getFlashName(std::string const& str) { return str + "___flash__"; }

void TextureManagerImpl::reset() { m_textures.clear(); }

size_t TextureManagerImpl::getNumberOfTextures() { return m_textures.size(); }

} // namespace jt
