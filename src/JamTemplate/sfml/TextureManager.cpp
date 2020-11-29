﻿#include "TextureManager.hpp"
#include <exception>
#include <map>

namespace jt {

namespace {

sf::Image createButtonImage(std::vector<std::string> const& ssv)
{
    if (ssv.size() != 3) {
        throw std::invalid_argument { "create button image: vector does not contain 3 elements." };
    }
    std::size_t count { 0 };
    long w = std::stol(ssv.at(1), &count);
    if (count != ssv.at(1).size()) {
        throw std::invalid_argument { "invalid button size string" };
    }
    long h = std::stol(ssv.at(2), &count);
    if (count != ssv.at(2).size()) {
        throw std::invalid_argument { "invalid button size string" };
    }
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument { "invalid button size" };
    }

    return SpriteFunctions::makeButtonImage(
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

void replaceOneColor(sf::Image& img, jt::color const& from, jt::color const& to)
{
    for (unsigned int x = 0U; x != img.getSize().x; ++x) {
        for (unsigned int y = 0U; y != img.getSize().y; ++y) {
            jt::color const c = img.getPixel(x, y);
            if (c == from) {
                img.setPixel(x, y, to);
            }
        }
    }
}

sf::Image createReplacedImage(std::vector<std::string> const& ssv,
    TextureManager::ColorReplaceLookupVectorType const& colorReplace)
{
    // "#r#assets/player.png#0"
    if (ssv.size() != 3) {
        throw std::invalid_argument { "create button image: vector does not contain 3 elements." };
    }
    if (colorReplace.empty()) {
        throw std::invalid_argument { "Color replace not possible, no color replacements stored." };
    }
    std::string baseFileName = ssv.at(1);
    std::size_t counter { 0 };
    auto idx = std::stoul(ssv.at(2), &counter);
    if (counter != ssv.at(2).size()) {
        throw std::invalid_argument { "invalid color replacement id" };
    }
    if (idx >= colorReplace.size()) {
        throw std::invalid_argument { "No color replacement for given index i= "
            + std::to_string(idx) };
    }

    sf::Image img {};
    img.loadFromFile(baseFileName);

    TextureManager::ColorReplaceLookupType const& cr = colorReplace.at(idx);
    if (cr.empty()) {
        // no color replacement to be done.
        return img;
    }

    for (auto const kvp : cr) {
        replaceOneColor(img, kvp.first, kvp.second);
    }

    return img;
}

sf::Image createFlashImage(sf::Image const& in)
{
    sf::Image img { in };

    for (unsigned int i = 0; i != img.getSize().x; ++i)
        for (unsigned int j = 0; j != img.getSize().y; ++j) {
            if (img.getPixel(i, j).a != 0) {
                img.setPixel(i, j, jt::color(255, 255, 255));
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

TextureManager::TextureMapType TextureManager::m_textures;
TextureManager::ColorReplaceLookupVectorType TextureManager::m_selectiveColorReplace {};

sf::Texture& TextureManager::get(std::string const& str)
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
            SplitString ss { str };
            auto ssv = ss.split('#');
            if (ssv.at(0) == "b") {
                m_textures[str].loadFromImage(createButtonImage(ssv));
            } else if (ssv.at(0) == "r") {
                m_textures[str].loadFromImage(createReplacedImage(ssv, m_selectiveColorReplace));
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

std::string TextureManager::getFlashName(std::string const& str) { return str + "___flash__"; }

void TextureManager::reset()
{
    m_textures.clear();
    m_selectiveColorReplace.clear();
}

} // namespace jt
