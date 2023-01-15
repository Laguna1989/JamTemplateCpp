#ifndef JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP
#define JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP

#include <graphics/drawable_impl.hpp>
#include <SFML/Graphics.hpp>

namespace jt {

class DrawableImplSFML : public jt::DrawableImpl {
protected:
    sf::BlendMode getSfBlendMode() const;

    jt::Vector2f getCompleteCamOffset() const;
};

} // namespace jt

#endif // JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP
