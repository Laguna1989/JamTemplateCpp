#ifndef GUARD_JAMTEMPLATE_SPRITE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SPRITE_HPP_INCLUDEGUARD

#include "color.hpp"
#include "drawable_impl.hpp"
#include "render_target.hpp"
#include "texture_manager_interface.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace jt {

class Sprite : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Sprite>;

    Sprite();

    Sprite(std::string const& fileName, jt::TextureManagerInterface& textureManager);
    Sprite(std::string const& fileName, jt::Recti const& rect,
        jt::TextureManagerInterface& textureManager);

    // DO NOT CALL THIS FROM GAME CODE!
    void fromTexture(sf::Texture const& text);

    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setFlashColor(jt::Color const& col) override;
    jt::Color getFlashColor() const override;

    virtual jt::Rectf getGlobalBounds() const override;
    virtual jt::Rectf getLocalBounds() const override;

    virtual void setScale(jt::Vector2f const& scale);
    virtual jt::Vector2f getScale() const;

    virtual void setOrigin(jt::Vector2f const& origin);
    virtual jt::Vector2f getOrigin() const;

    // WARNING: This function is slow, because it needs to copy
    // graphics memory to ram first.
    jt::Color getColorAtPixel(jt::Vector2u pixelPos) const;

    void cleanImage();

    // DO NOT CALL THIS FROM GAME CODE!
    sf::Sprite getSFSprite() { return m_sprite; }

private:
    mutable sf::Sprite m_sprite;
    sf::Sprite m_flashSprite;
    // optimization for getColorAtPixel
    mutable sf::Image m_image;
    mutable bool m_imageStored { false };

    jt::Vector2f m_position { 0, 0 };

    void doUpdate(float /*elapsed*/) override;

    void doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const override;
    void doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    void doRotate(float rot);
};

} // namespace jt

#endif
