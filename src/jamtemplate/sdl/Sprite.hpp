#ifndef GUARD_JAMTEMPLATE_SPRITE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SPRITE_HPP_INCLUDEGUARD

#include "Color.hpp"
#include "DrawableImpl.hpp"
#include "Rendertarget.hpp"
#include "Vector.hpp"
#include <SDL.h>
#include <memory>
#include <string>

namespace jt {

class Sprite : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Sprite>;

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

    virtual void setScale(jt::Vector2 const& scale) override;
    virtual const jt::Vector2 getScale() const override;

    virtual void setOrigin(jt::Vector2 const& origin) override;
    virtual jt::Vector2 const getOrigin() const override;

    // WARNING: This function is slow, because it needs to copy
    // graphics memory to ram first.
    jt::Color getColorAtPixel(jt::Vector2u pixelPos) const;
    // clean up stored image
    void cleanImage();

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::Vector2 m_position { 0, 0 };
    jt::Recti m_sourceRect { 0, 0, 0, 0 };
    jt::Color m_color { jt::colors::White };
    jt::Vector2 m_scale { 1.0f, 1.0f };
    jt::Vector2 m_origin { 0.0f, 0.0f };

    mutable std::shared_ptr<SDL_Texture> m_textFlash;
    jt::Color m_colorFlash { jt::colors::White };
    std::string m_fileName { "" };

    mutable std::shared_ptr<SDL_Surface> m_image { nullptr };

    void doUpdate(float /*elapsed*/) override;

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doRotate(float /*rot*/) override;

    SDL_Rect getDestRect(jt::Vector2 const& positionOffset = jt::Vector2 { 0.0f, 0.0f }) const;
    SDL_Rect getSourceRect() const;
    void setSDLColor(jt::Color const& col) const;
};

} // namespace jt

#endif
