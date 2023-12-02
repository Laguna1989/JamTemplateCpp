#ifndef JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP
#define JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP

#include <sdl_2_include.hpp>
#include <cstddef>
#include <memory>
#include <string>

namespace jt {
class TextureManagerInterface {
public:

    /// get texture for string
    /// \param str texture identifier
    /// \return shared pointer to SDL_Texture
    virtual std::shared_ptr<SDL_Texture> get(std::string const& str) = 0;

    /// reset the texture manager
    virtual void reset() = 0;

    /// get flash version of texture identifier
    /// \param str texture identifier
    /// \return texture identifier with flash postfix
    virtual std::string getFlashName(std::string const& str) = 0;

    /// get number of textures
    /// \return the number of textures
    virtual std::size_t getNumberOfTextures() noexcept = 0;

    virtual ~TextureManagerInterface() = default;
};
} // namespace jt

#endif // JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP
