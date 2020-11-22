#ifndef RENDERTARGET_BASE_GUARD_HPP
#define RENDERTARGET_BASE_GUARD_HPP

#include <SFML/Graphics.hpp>

namespace jt {

class renderTarget : public sf::RenderTexture {
    using sf::RenderTexture::RenderTexture;
};

} // namespace jt

#endif
