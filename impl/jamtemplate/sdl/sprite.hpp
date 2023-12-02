#ifndef JAMTEMPLATE_SPRITE_HPP
#define JAMTEMPLATE_SPRITE_HPP

#include <color/color.hpp>
#include <drawable_impl_sdl.hpp>
#include <render_target_layer.hpp>
#include <sdl_2_include.hpp>
#include <texture_manager_interface.hpp>
#include <vector.hpp>
#include <memory>
#include <string>

namespace jt {

class Sprite : public DrawableImplSdl {
public:
    using Sptr = std::shared_ptr<Sprite>;

    Sprite();

    Sprite(std::string const& fileName, jt::TextureManagerInterface& textureManager);
    Sprite(std::string const& fileName, jt::Recti const& rect,
        jt::TextureManagerInterface& textureManager);

    // DO NOT CALL THIS FROM GAME CODE!
    void fromTexture(std::shared_ptr<SDL_Texture> const& txt);

    // WARNING: This function is slow, because it needs to copy
    // graphics memory to ram first.
    jt::Color getColorAtPixel(jt::Vector2u pixelPos) const;

    void cleanImage() noexcept;


    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    virtual jt::Rectf getGlobalBounds() const override;
    virtual jt::Rectf getLocalBounds() const override;

    virtual void setScale(jt::Vector2f const& scale) override;
    virtual jt::Vector2f getScale() const override;

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::Vector2f m_position { 0, 0 };
    jt::Recti m_sourceRect { 0, 0, 0, 0 };
    jt::Color m_color { jt::colors::White };

    mutable std::shared_ptr<SDL_Texture> m_textFlash;
    std::string m_fileName { "" };

    mutable std::shared_ptr<SDL_Surface> m_image { nullptr };

    void doUpdate(float /*elapsed*/) override;

    void doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doRotate(float /*rot*/) noexcept override;

    SDL_Rect getDestRect(jt::Vector2f const& positionOffset = jt::Vector2f { 0.0f, 0.0f }) const;
    SDL_Rect getSourceRect() const;
    void setSDLColor(jt::Color const& col) const;
};

} // namespace jt

#endif
