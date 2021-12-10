#ifndef GUARD_JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP

#include "color.hpp"
#include "render_target.hpp"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {
class TextureManagerInterface {
public:
    virtual ~TextureManagerInterface() = default;
    virtual sf::Texture& get(std::string const& str) = 0;
    virtual void reset() = 0;
    virtual std::string getFlashName(std::string const& str) = 0;
    virtual std::size_t getNumberOfTextures() = 0;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TEXTURE_MANAGER_INTERFACE_HPP
