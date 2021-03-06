﻿#ifndef GUARD_JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include "Color.hpp"
#include "Rendertarget.hpp"
#include "SmartDrawable.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace jt {

class SmartSprite : public SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartSprite>;

    void loadSprite(std::string const& fileName);

    void loadSprite(std::string const& fileName, jt::Recti const& rect);

    void setPosition(jt::Vector2 const& pos) override;

    const jt::Vector2 getPosition() const override;

    void setColor(jt::Color const& col) override;
    const jt::Color getColor() const override;

    void setFlashColor(jt::Color const& col) override;
    const jt::Color getFlashColor() const override;

    // virtual sf::Transform const getTransform() const override { return m_sprite.getTransform(); }

    virtual jt::Rect const getGlobalBounds() const override;
    virtual jt::Rect const getLocalBounds() const override;

    virtual void setScale(jt::Vector2 const& scale);

    virtual const jt::Vector2 getScale() const;

    virtual void setOrigin(jt::Vector2 const& origin);

    virtual jt::Vector2 const getOrigin() const;

    // WARNING: This function is slow, because it needs to copy
    // graphics memory to ram first.
    jt::Color getColorAtPixel(jt::Vector2u pixelPos) const;

    void cleanImage();

private:
    mutable sf::Sprite m_sprite;
    sf::Sprite m_flashSprite;
    // optimization for getColorAtPixel
    mutable sf::Image m_image;
    mutable bool m_imageStored { false };

    jt::Vector2 m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override;

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doRotate(float rot);
};

} // namespace jt

#endif
