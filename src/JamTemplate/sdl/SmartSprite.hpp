#ifndef GUARD_JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include "SmartDrawable.hpp"
#include "color.hpp"
#include "rendertarget.hpp"
#include "vector.hpp"
#include <SDL.h>
#include <memory>
#include <string>

namespace jt {

class SmartSprite : public SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartSprite>;

    void loadSprite(std::string const& fileName);
    void loadSprite(std::string const& fileName, jt::recti const& rect);

    void setPosition(jt::vector2 const& pos) override;
    const jt::vector2 getPosition() const override;

    void setColor(jt::color const& col) override;
    const jt::color getColor() const override;

    void setFlashColor(jt::color const& col) override;
    const jt::color getFlashColor() const override;

    // virtual sf::Transform const getTransform() const override { return m_sprite.getTransform(); }

    virtual jt::rect const getGlobalBounds() const override;
    virtual jt::rect const getLocalBounds() const override;

    virtual void setScale(jt::vector2 const& scale) override;
    virtual const jt::vector2 getScale() const override;

    virtual void setOrigin(jt::vector2 const& origin) override;
    virtual jt::vector2 const getOrigin() const override;

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::vector2 m_position { 0, 0 };
    jt::recti m_sourceRect { 0, 0, 0, 0 };
    jt::color m_color { jt::colors::White };
    jt::vector2 m_scale { 1.0f, 1.0f };
    jt::vector2 m_origin { 0.0f, 0.0f };

    mutable std::shared_ptr<SDL_Texture> m_textFlash;
    jt::color m_colorFlash { jt::colors::White };

    void doUpdate(float /*elapsed*/) override;

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doRotate(float /*rot*/) override;

    SDL_Rect getDestRect(jt::vector2 const& positionOffset = jt::vector2 { 0.0f, 0.0f }) const;
    SDL_Rect getSourceRect() const;
    void setSDLColor(jt::color const& col) const;
};

} // namespace jt

#endif
