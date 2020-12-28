#ifndef GUARD_JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD

#include "Color.hpp"
#include "Rendertarget.hpp"
#include "SplitString.hpp"
#include <SDL.h>
#include <assert.h>
#include <exception>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class TextureManager {
public:
    using ColorReplaceLookupType = std::vector<std::pair<jt::Color, jt::Color>>;
    using ColorReplaceLookupVectorType = std::vector<ColorReplaceLookupType>;
    using TextureMapType = std::map<std::string, std::shared_ptr<SDL_Texture>>;
    TextureManager() = delete;

    // get texture from string
    // str can be any filename/filepath
    // str can be a special string, e.g.
    // - #b#100#200 will create a button with width 100 and height 200
    // - #r#assets/player.png#0 will load player.png and perform color replace number 0
    static std::shared_ptr<SDL_Texture> get(std::string const& str);

    // reset all stored images
    static void reset();

    static std::string getFlashName(std::string const& str);

    // This will chance all textures and might not be revertible.
    // Warning: due to slow copy process from graphics memory to ram and back to graphics this
    // should not be called frequently! Only works for textures obtained from this class (not for
    // colors of shapes or whatever) \param in and out are used for lookups if a color is used which
    // is not contained in in, the color will be unchanged
    static void swapPalette(std::vector<jt::Color> /*in*/, std::vector<jt::Color> /*out*/)
    {
        throw std::logic_error { "swap palette not supported yet" };
    }

    static void addSelectiveColorReplacement(
        int /*idx*/, std::vector<std::pair<jt::Color, jt::Color>> /*replace*/)
    {
        throw std::logic_error { "color replacement not supported yet" };
    }
    static void setRenderer(std::weak_ptr<jt::renderTarget> renderer) { m_renderer = renderer; };

private:
    static TextureMapType m_textures;
    static ColorReplaceLookupVectorType m_selectiveColorReplace;
    static std::weak_ptr<jt::renderTarget> m_renderer;
    static bool containsTexture(std::string const& str) { return (m_textures.count(str) != 0); }
};

} // namespace jt

#endif
