#ifndef GUARD_JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP

#include "render_target.hpp"
#include <SDL2/SDL.h>
#include <cstddef>
#include <memory>
#include <string>

namespace jt {
class TextureManagerInterface {
public:
    virtual ~TextureManagerInterface() = default;
    virtual std::shared_ptr<SDL_Texture> get(std::string const& str) = 0;
    virtual void reset() = 0;
    virtual std::string getFlashName(std::string const& str) = 0;
    virtual std::size_t getNumberOfTextures() = 0;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP
