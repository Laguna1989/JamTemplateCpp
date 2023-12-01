#ifndef JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP
#define JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP

#include <SFML/Graphics.hpp>
#include <graphics/drawable_impl.hpp>

namespace jt {

class DrawableImplSFML : public jt::DrawableImpl {
protected:
    /// get sf blend mode
    /// \return the sf::BlendMode
    sf::BlendMode getSfBlendMode() const;

    /// get complete cam offset
    /// \return the cam offset in pixel
    jt::Vector2f getCompleteCamOffset() const;
};

} // namespace jt

#endif // JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP
