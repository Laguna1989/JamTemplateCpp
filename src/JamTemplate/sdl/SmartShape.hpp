#ifndef GUARD_JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD

#include "SmartDrawable.hpp"
#include "rect.hpp"
#include "rendertarget.hpp"
#include "vector.hpp"
#include <SDL.h>
#include <memory>

namespace jt {
class SmartShape : public SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartShape>;

    void makeRect(jt::vector2 size);

    void setColor(jt::color const& col) override;
    const jt::color getColor() const override;

    void setFlashColor(jt::color const& col) override;
    const jt::color getFlashColor() const override;

    void setPosition(jt::vector2 const& pos) override;
    const jt::vector2 getPosition() const override;

    // sf::Transform const getTransform() const override { return m_shape->getTransform(); }

    jt::rect const getGlobalBounds() const override;
    jt::rect const getLocalBounds() const override;

    void setScale(jt::vector2 const& scale) override;
    const jt::vector2 getScale() const override;

    void setOrigin(jt::vector2 const& origin) override;
    const jt::vector2 getOrigin() const override;

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::vector2 m_position { 0, 0 };
    jt::recti m_sourceRect { 0, 0, 0, 0 };
    jt::color m_color { jt::colors::White };
    jt::vector2 m_scale { 1.0f, 1.0f };
    jt::vector2 m_origin { 0.0f, 0.0f };
    jt::color m_colorFlash { jt::colors::White };

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doUpdate(float /*elapsed*/) override;
    void doRotate(float /*rot*/) override;

    SDL_Rect getDestRect(jt::vector2 const& positionOffset = jt::vector2 { 0, 0 }) const;

    void setSDLColor(jt::color const& col) const;
};
} // namespace jt

#endif
