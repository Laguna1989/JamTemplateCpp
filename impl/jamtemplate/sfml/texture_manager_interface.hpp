#ifndef JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP
#define JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP

#include <render_target_layer.hpp>
#include <cstddef>
#include <string>

namespace sf {
class Texture;
}

namespace jt {
class TextureManagerInterface {
public:
    /// get texture for string
    /// \param str texture identifier
    /// \return reference to sf::Texture
    virtual sf::Texture& get(std::string const& str) = 0;

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
