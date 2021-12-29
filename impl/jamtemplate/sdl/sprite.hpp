#ifndef GUARD_JAMTEMPLATE_SPRITE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SPRITE_HPP_INCLUDEGUARD

#include "color.hpp"
#include "drawable_impl.hpp"
#include "render_target.hpp"
#include "texture_manager_interface.hpp"
#include "vector.hpp"
#include <SDL2/SDL.h>
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
    void fromTexture(std::shared_ptr<SDL_Texture> txt);

    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setFlashColor(jt::Color const& col) override;
    jt::Color getFlashColor() const override;

    virtual jt::Rectf getGlobalBounds() const override;
    virtual jt::Rectf getLocalBounds() const override;

    virtual void setScale(jt::Vector2f const& scale) override;
    virtual jt::Vector2f getScale() const override;

    virtual void setOrigin(jt::Vector2f const& origin) override;
    virtual jt::Vector2f getOrigin() const override;

    // WARNING: This function is slow, because it needs to copy
    // graphics memory to ram first.
    jt::Color getColorAtPixel(jt::Vector2u pixelPos) const;

    void cleanImage();

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::Vector2f m_position { 0, 0 };
    jt::Recti m_sourceRect { 0, 0, 0, 0 };
    jt::Color m_color { jt::colors::White };
    jt::Vector2f m_scale { 1.0f, 1.0f };
    jt::Vector2f m_origin { 0.0f, 0.0f };
    jt::Vector2f m_offsetFromOrigin { 0.0f, 0.0f };

    mutable std::shared_ptr<SDL_Texture> m_textFlash;
    jt::Color m_colorFlash { jt::colors::White };
    std::string m_fileName { "" };

    mutable std::shared_ptr<SDL_Surface> m_image { nullptr };

    void doUpdate(float /*elapsed*/) override;

    void doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    void doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const override;
    void doRotate(float /*rot*/) override;

    SDL_Rect getDestRect(jt::Vector2f const& positionOffset = jt::Vector2f { 0.0f, 0.0f }) const;
    SDL_Rect getSourceRect() const;
    void setSDLColor(jt::Color const& col) const;
};

} // namespace jt

#endif
