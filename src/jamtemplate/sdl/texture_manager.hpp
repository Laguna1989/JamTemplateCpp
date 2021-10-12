#ifndef GUARD_JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD

#include "color.hpp"
#include "render_target.hpp"
#include "splitstring.hpp"
#include <SDL2/SDL.h>
#include <assert.h>
#include <exception>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class TextureManager {
public:
    using TextureMapType = std::map<std::string, std::shared_ptr<SDL_Texture>>;
    TextureManager() = delete;

    // get texture from string
    // str can be any filename/filepath
    // str can be a special string, e.g.
    // - #b#100#200 will create a button with width 100 and height 200
    static std::shared_ptr<SDL_Texture> get(std::string const& str);

    // reset all stored images
    static void reset();

    static std::string getFlashName(std::string const& str);

    static void setRenderer(std::weak_ptr<jt::renderTarget> renderer) { m_renderer = renderer; };

private:
    static TextureMapType m_textures;
    static std::weak_ptr<jt::renderTarget> m_renderer;
    static bool containsTexture(std::string const& str) { return (m_textures.count(str) != 0); }
};

} // namespace jt

#endif
