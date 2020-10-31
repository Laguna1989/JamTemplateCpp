#ifndef JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>
#include <assert.h>
#include <map>
#include <string>
#include <vector>

#include "SplitString.hpp"
#include "SpriteFunctions.hpp"

namespace JamTemplate {

class TextureManager {
public:
    using ColorReplaceLookupType = std::vector<std::pair<sf::Color, sf::Color>>;
    using ColorReplaceLookupVectorType = std::vector<ColorReplaceLookupType>;
    using TextureMapType = std::map<std::string, sf::Texture>;
    TextureManager() = delete;

    // get texture from string
    // str can be any filename/filepath
    // str can be a special string, e.g.
    // - #b#100#200 will create a button with width 100 and height 200
    // - #r#assets/player.png#0 will load player.png and perform color replace number 0
    static sf::Texture& get(std::string const& str);

    // reset all stored images
    static void reset();

    static std::string TextureManager::getFlashName(std::string const& str);

    // This will chance all textures and might not be revertible.
    // Warning: due to slow copy process from graphics memory to ram and back to graphics this
    // should not be called frequently! Only works for textures obtained from this class (not for
    // colors of shapes or whatever) \param in and out are used for lookups if a color is used which
    // is not contained in in, the color will be unchanged
    static void swapPalette(std::vector<sf::Color> in, std::vector<sf::Color> out)
    {
        assert(in.size() == out.size());
        for (auto& kvp : m_textures) {

            sf::Image img = kvp.second.copyToImage();

            for (unsigned i = 0; i != img.getSize().x; ++i)
                for (unsigned j = 0; j != img.getSize().x; ++j) {
                    auto col = img.getPixel(i, j);
                    // for this pixel check for each color in lookup
                    for (size_t idx = 0; idx != in.size(); ++idx) {
                        if (in[idx] == col) {
                            img.setPixel(i, j, out[idx]);
                            break;
                        }
                    }
                }
            kvp.second.loadFromImage(img);
        }
    }

    static bool isTextureLoaded(std::string filename) { return m_textures.count(filename) != 0; }

    static void addTexture(std::string name, sf::Texture& t) { m_textures[name] = (t); }

    static void addSelectiveColorReplacement(
        int idx, std::vector<std::pair<sf::Color, sf::Color>> replace)
    {
        if (m_selectiveColorReplace.size() <= idx) {
            m_selectiveColorReplace.resize(idx + 1U);
        }

        m_selectiveColorReplace.at(idx) = replace;
    }

private:
    static TextureMapType m_textures;
    static ColorReplaceLookupVectorType m_selectiveColorReplace;

    static bool containsTexture(std::string const& str) { return (m_textures.count(str) != 0); }
};

} // namespace JamTemplate

#endif
