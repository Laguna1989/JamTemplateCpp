#include "texture_manager_impl.hpp"
#include "color_lib.hpp"
#include "sprite_functions.hpp"
#include "strutils.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>

namespace jt {
namespace {

sf::Image createButtonImage(std::vector<std::string> const& ssv)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument { "create button image: vector does not contain 3 elements." };
    }
    std::size_t count { 0 };
    std::int64_t w = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size()) {
        throw std::invalid_argument { "invalid button size string" };
    }
    std::int64_t h = std::stol(ssv.at(2), &count);
    if (count != ssv.at(2).size()) {
        throw std::invalid_argument { "invalid button size string" };
    }
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument { "invalid button size" };
    }

    return SpriteFunctions::makeButtonImage(
        static_cast<unsigned int>(w), static_cast<unsigned int>(h));
}

sf::Image createBlankImage(std::vector<std::string> const& ssv)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument { "create blank image: vector does not contain 3 elements." };
    }
    std::size_t count { 0 };
    std::int64_t w = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size()) {
        throw std::invalid_argument { "invalid image size string" };
    }
    std::int64_t h = std::stol(ssv.at(2), &count);
    if (count != ssv.at(2).size()) {
        throw std::invalid_argument { "invalid image size string" };
    }
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument { "invalid image size" };
    }

    return SpriteFunctions::makeBlankImage(
        static_cast<unsigned int>(w), static_cast<unsigned int>(h));
}

sf::Image createGlowImage(std::vector<std::string> const& ssv)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument { "create glow image: vector does not contain 2 elements." };
    }
    std::size_t count { 0 };
    auto const s = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size() || s <= 0) {
        throw std::invalid_argument { "invalid glow size" };
    }
    auto const max = std::stol(ssv.at(2), &count);
    if (count != ssv.at(2).size() || max <= 0 || max > 255) {
        throw std::invalid_argument { "invalid glowmax" };
    }
    return SpriteFunctions::makeGlowImage(static_cast<float>(s), static_cast<uint8_t>(max));
}

sf::Image createVignetteImage(std::vector<std::string> const& ssv)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument {
            "create vignette image: vector does not contain 2 elements."
        };
    }
    std::size_t count { 0 };
    auto w = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size() || w <= 0) {
        throw std::invalid_argument { "invalid vignette w" };
    }
    auto h = std::stol(ssv.at(2), &count);
    if (count != ssv.at(2).size() || h <= 0) {
        throw std::invalid_argument { "invalid vignette h" };
    }
    return SpriteFunctions::makeVignetteImage(w, h);
}

sf::Image createFlashImage(sf::Image const& in)
{
    sf::Image img { in };

    for (unsigned int i = 0; i != img.getSize().x; ++i) {
        for (unsigned int j = 0; j != img.getSize().y; ++j) {
            if (img.getPixel(i, j).a != 0) {
                img.setPixel(i, j, toLib(jt::Color { 255, 255, 255 }));
            }
        }
    }
    return img;
}

sf::Texture loadTextureFromDisk(std::string const& str)
{
    sf::Texture t {};
    if (!t.loadFromFile(str)) {
        throw std::invalid_argument { "invalid filename, cannot load texture from '" + str + "'" };
    }
    return t;
}
} // namespace

TextureManagerImpl::TextureManagerImpl(std::shared_ptr<jt::RenderTarget> /*renderer*/)
{
    // Nothing to do here
}

sf::Texture& TextureManagerImpl::get(std::string const& str)
{
    if (str.empty()) {
        throw std::invalid_argument { "TextureManager get: string must not be empty" };
    }

    // check if texture is already stored in texture manager
    if (!containsTexture(str)) {
        // normal filenames do not start with a '#'
        if (str.at(0) != '#') {
            m_textures[str] = loadTextureFromDisk(str);
        } else // special type of images
        {
            auto ssv = strutil::split(str.substr(1), '#');
            if (ssv.at(0) == "b") {
                m_textures[str].loadFromImage(createButtonImage(ssv));
            } else if (ssv.at(0) == "f") {
                m_textures[str].loadFromImage(createBlankImage(ssv));
            } else if (ssv.at(0) == "g") {
                m_textures[str].loadFromImage(createGlowImage(ssv));
            } else if (ssv.at(0) == "v") {
                m_textures[str].loadFromImage(createVignetteImage(ssv));
            } else {
                throw std::invalid_argument("ERROR: cannot get texture with name " + str);
            }
        }

        // create Flash Image
        m_textures[getFlashName(str)].loadFromImage(
            createFlashImage(m_textures[str].copyToImage()));
    }

    return m_textures[str];
}
void TextureManagerImpl::reset() { m_textures.clear(); }
std::string TextureManagerImpl::getFlashName(std::string const& str) { return str + "___flash__"; }
std::size_t TextureManagerImpl::getNumberOfTextures() { return m_textures.size(); }

} // namespace jt
