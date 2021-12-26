#ifndef GUARD_JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD

#include "render_target.hpp"
#include "texture_manager_interface.hpp"
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>

namespace jt {

class TextureManagerImpl : public jt::TextureManagerInterface {
public:
    TextureManagerImpl(std::shared_ptr<jt::renderTarget> renderer);
    std::shared_ptr<SDL_Texture> get(std::string const& str);

    // reset all stored images
    void reset() override;

    std::string getFlashName(std::string const& str);

    std::size_t getNumberOfTextures() override;

private:
    std::map<std::string, std::shared_ptr<SDL_Texture>> m_textures;
    std::weak_ptr<jt::renderTarget> m_renderer;
    bool containsTexture(std::string const& str) { return (m_textures.count(str) != 0); }
};

} // namespace jt

#endif
