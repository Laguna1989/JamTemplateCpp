#include "texture_manager_impl.hpp"
#include <aselib/image_builder.hpp>
#include <sdl_helper.hpp>
#include <sprite_functions.hpp>
#include <strutils.hpp>
#include <SDL_image.h>
#include <tracy/Tracy.hpp>
#include <array>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace jt {

namespace {

std::shared_ptr<SDL_Texture> createImageFromAse(
    std::string const& filename, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
{
    auto const asepritePos = filename.rfind(".aseprite");
    auto const splittedFilename = filename.substr(0, asepritePos + 9);
    auto const postFix = filename.substr(asepritePos + 9);
    aselib::AsepriteData aseData { filename };

    std::unique_ptr<aselib::Image> aseImage { nullptr };
    if (strutil::contains(postFix, ".layer=")) {
        auto const layerPos = postFix.find(".layer=");
        auto const layerName = postFix.substr(layerPos + 7);
        aseImage = std::make_unique<aselib::Image>(aselib::makeImageFromLayer(aseData, layerName));
    } else {
        auto const ignore_transparent = strutil::contains(postFix, ".ignore_transparent");
        aseImage = std::make_unique<aselib::Image>(
            aselib::makeImageFromAse(aseData, !ignore_transparent));
    }

    auto const w = aseImage->m_width;
    auto const h = aseImage->m_height;
    auto const wAsInt = static_cast<int>(w);
    auto const hAsInt = static_cast<int>(h);
    std::shared_ptr<SDL_Surface> image = std::shared_ptr<SDL_Surface>(
        SDL_CreateRGBSurfaceWithFormat(0, wAsInt, hAsInt, 32, SDL_PIXELFORMAT_RGBA32),
        [](SDL_Surface* s) { SDL_FreeSurface(s); });

    auto const transparent = SDL_MapRGBA(image->format, 0, 0, 0, 0);

    for (auto i = 0u; i != w; ++i) {
        for (auto j = 0u; j != h; ++j) {
            jt::setPixel(image.get(), i, j, transparent);
        }
    }

    for (auto i = 0u; i != w; ++i) {
        for (auto j = 0u; j != h; ++j) {
            auto const& p = aseImage->getPixelAt(i, j);
            auto const col = SDL_MapRGBA(image->format, p.r, p.g, p.b, p.a);
            jt::setPixel(image.get(), i, j, col);
        }
    }
    return std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderTarget.get(), image.get()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });
}

std::shared_ptr<SDL_Texture> createButtonImage(
    std::array<std::string, 3> const& ssv, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
{
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
    std::array<std::string, 3> const& ssv, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
{
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
    std::array<std::string, 3> const& ssv, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
{
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
    std::array<std::string, 3> const& ssv, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
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
    std::array<std::string, 3> const& ssv, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
{
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
    std::array<std::string, 2> const& ssv, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
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

std::shared_ptr<SDL_Texture> createRingImage(
    std::array<std::string, 2> const& ssv, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
{
    if (ssv.size() != 2) {
        throw std::invalid_argument { "create ring image: vector does not contain 1 elements." };
    }
    std::size_t count { 0 };
    auto const ringImageSize = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size() || ringImageSize <= 0) {
        throw std::invalid_argument { "invalid ring image size" };
    }

    return SpriteFunctions::makeRing(renderTarget, ringImageSize);
}

std::shared_ptr<SDL_Texture> createFlashImage(
    std::string const& str, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
{
    auto image = std::shared_ptr<SDL_Surface>(
        IMG_Load(str.c_str()), [](SDL_Surface* s) { SDL_FreeSurface(s); });
    if (!image) {
        return nullptr;
    }
    int const w = image->w;
    int const h = image->h;

    auto const white = SDL_MapRGBA(image->format, 255u, 255u, 255u, 255u);

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
    std::string const& str, std::shared_ptr<jt::RenderTargetLayer> renderTarget)
{
    if (renderTarget == nullptr) {
        throw std::logic_error { "rendertarget is null in loadTextureFromDisk" };
    }
    auto texture = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderTarget.get(), str.c_str()),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); });

    if (texture == nullptr) {
        throw std::invalid_argument { "invalid filename, cannot load texture from '" + str + "'" };
    }
    return texture;
}
} // namespace

TextureManagerImpl::TextureManagerImpl(std::shared_ptr<jt::RenderTargetLayer> renderer)
{
    m_renderer = renderer;
}

std::shared_ptr<SDL_Texture> TextureManagerImpl::get(std::string const& str)
{
    ZoneScopedNC("jt::TextureManagerImpl::get", tracy::Color::Crimson);
    if (str.empty()) {
        std::cout << "TextureManager get: string must not be empty" << std::endl;
        throw std::invalid_argument { "TextureManager get: string must not be empty" };
    }
    auto renderer = m_renderer.lock();
    if (!renderer) {
        std::cout << "renderer not available for TextureManager::get()" << std::endl;
        throw std::logic_error { "renderer not available for TextureManager::get()" };
    }

    // check if texture is already stored in texture manager
    if (containsTexture(str)) {
        ZoneColor(tracy::Color::AntiqueWhite2);
        return m_textures[str];
    }

    // Check if special ase parsing is required
    if (strutil::contains(str, ".aseprite")) {
        m_textures[str] = createImageFromAse(str, renderer);
        m_textures[getFlashName(str)] = createFlashImage(str, renderer);
        return m_textures[str];
    }

    // normal filenames do not start with a '#'
    if (!str.starts_with('#')) {
        m_textures[str] = loadTextureFromDisk(str, m_renderer.lock());
        // create Flash Image
        m_textures[getFlashName(str)] = createFlashImage(str, m_renderer.lock());
        return m_textures[str];
    }

    if (str.at(1) == 'b') {
        auto ssv = strutil::split<3>(str.substr(1u), '#');
        m_textures[str] = createButtonImage(ssv, renderer);
    } else if (str.at(1) == 'f') {
        auto ssv = strutil::split<3>(str.substr(1u), '#');
        m_textures[str] = createBlankImage(ssv, renderer);
    } else if (str.at(1) == 'g') {
        auto ssv = strutil::split<3>(str.substr(1u), '#');
        m_textures[str] = createGlowImage(ssv, renderer);
    } else if (str.at(1) == 'v') {
        auto ssv = strutil::split<3>(str.substr(1u), '#');
        m_textures[str] = createVignetteImage(ssv, renderer);
    } else if (str.at(1) == 'x') {
        auto ssv = strutil::split<3>(str.substr(1u), '#');
        m_textures[str] = createRectImage(ssv, renderer);
    } else if (str.at(1) == 'c') {
        auto ssv = strutil::split<2>(str.substr(1u), '#');
        m_textures[str] = createCircleImage(ssv, renderer);
    } else if (str.at(1) == 'r') {
        auto ssv = strutil::split<2>(str.substr(1u), '#');
        m_textures[str] = createRingImage(ssv, renderer);
    } else {
        throw std::invalid_argument("ERROR: cannot get texture with name " + str);
    }

    // create Flash Image
    m_textures[getFlashName(str)] = m_textures[str];

    return m_textures[str];
}

std::string TextureManagerImpl::getFlashName(std::string const& str) { return str + "___flash__"; }

void TextureManagerImpl::reset() { m_textures.clear(); }

size_t TextureManagerImpl::getNumberOfTextures() noexcept { return m_textures.size(); }

} // namespace jt
