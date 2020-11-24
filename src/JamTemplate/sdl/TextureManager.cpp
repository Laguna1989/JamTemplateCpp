#include "TextureManager.hpp"
#include <SDL_image.h>
#include <map>

namespace JamTemplate {

namespace {

// sf::Image createButtonImage(std::vector<std::string> const& ssv)
// {
//     // TODO
// }

// sf::Image createGlowImage(std::vector<std::string> const& ssv)
// {
//     // TODO
// }

// sf::Image createVignetteImage(std::vector<std::string> const& ssv)
// {
//     // TODO
// }

// void replaceOneColor(sf::Image& img, jt::color const& from, jt::color const& to)
// {
//     // TODO
// }

// sf::Image createReplacedImage(std::vector<std::string> const& ssv,
//     TextureManager::ColorReplaceLookupVectorType const& colorReplace)
// {
//     // TODO
// }

// sf::Image createFlashImage(sf::Image const& in)
// {
//     // TODO
// }

std::shared_ptr<SDL_Texture> loadTextureFromDisk(
    std::string const& str, std::shared_ptr<jt::renderTarget> rt)
{
    if (rt == nullptr) {
        throw std::logic_error { "rendertarget is null in loadTextureFromDisk" };
    }
    auto t = std::shared_ptr<SDL_Texture>(
        IMG_LoadTexture(rt.get(), str.c_str()), [](SDL_Texture* t) { SDL_DestroyTexture(t); });

    if (t == nullptr) {
        throw std::invalid_argument { "invalid filename, cannot load texture from '" + str + "'" };
    }
    return t;
}
} // namespace

TextureManager::TextureMapType TextureManager::m_textures;
TextureManager::ColorReplaceLookupVectorType TextureManager::m_selectiveColorReplace {};
std::weak_ptr<jt::renderTarget> TextureManager::m_renderer {};

std::shared_ptr<SDL_Texture> TextureManager::get(std::string const& str)
{
    if (str.empty()) {
        throw std::invalid_argument { "TextureManager get: string must not be empty" };
    }
    if (m_renderer.expired()) {
        throw std::logic_error { "renderer not available for TextureManager::get()" };
    }

    // check if texture is already stored in texture manager
    if (!containsTexture(str)) {
        // normal filenames do not start with a '#'
        if (str.at(0) != '#') {
            m_textures[str] = loadTextureFromDisk(str, m_renderer.lock());
        } else // special type of images
        {
            SplitString ss { str };
            auto ssv = ss.split('#');
            if (ssv.at(0) == "b") {
                // m_textures[str].loadFromImage(createButtonImage(ssv));
            } else if (ssv.at(0) == "r") {
                // m_textures[str].loadFromImage(createReplacedImage(ssv, m_selectiveColorReplace));
            } else if (ssv.at(0) == "g") {
                // m_textures[str].loadFromImage(createGlowImage(ssv));
            } else if (ssv.at(0) == "v") {
                // m_textures[str].loadFromImage(createVignetteImage(ssv));
            } else {
                throw std::invalid_argument("ERROR: cannot get texture with name " + str);
            }
        }

        // create Flash Image
        // m_textures[getFlashName(str)].loadFromImage(
        //     createFlashImage(m_textures[str].copyToImage()));
    }

    return m_textures[str];
}

std::string TextureManager::getFlashName(std::string const& str) { return str + "___flash__"; }

void TextureManager::reset()
{
    m_textures.clear();
    m_selectiveColorReplace.clear();
}

} // namespace JamTemplate
