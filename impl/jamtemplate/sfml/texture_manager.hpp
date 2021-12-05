#ifndef GUARD_JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD

#include "render_target.hpp"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class StaticTextureManager {
public:
    using TextureMapType = std::map<std::string, sf::Texture>;
    StaticTextureManager() = delete;

    static sf::Texture& get(std::string const& str);

    // reset all stored textures
    static void reset();

    static std::string getFlashName(std::string const& str);

    static void setRenderer(std::weak_ptr<jt::renderTarget> /*unused*/) {};

private:
    static TextureMapType m_textures;
    static bool containsTexture(std::string const& str) { return (m_textures.count(str) != 0); }
};

} // namespace jt

#endif
