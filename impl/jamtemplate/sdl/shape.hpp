#ifndef JAMTEMPLATE_SHAPE_HPP
#define JAMTEMPLATE_SHAPE_HPP

#include <drawable_impl_sdl.hpp>
#include <rect.hpp>
#include <render_target_layer.hpp>
#include <sdl_2_include.hpp>
#include <texture_manager_interface.hpp>
#include <vector.hpp>
#include <memory>

namespace jt {
class Shape : public DrawableImplSdl {
public:
    using Sptr = std::shared_ptr<Shape>;

    void makeRect(jt::Vector2f size, jt::TextureManagerInterface& textureManager);
    void makeCircle(float radius, jt::TextureManagerInterface& textureManager);

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    void setScale(jt::Vector2f const& scale) override;
    jt::Vector2f getScale() const override;

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::Vector2f m_position { 0, 0 };
    jt::Recti m_sourceRect { 0, 0, 0, 0 };
    jt::Color m_color { jt::colors::White };

    void doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;

    void doUpdate(float /*elapsed*/) noexcept override;
    void doRotate(float /*rot*/) noexcept override;

    SDL_Rect getDestRect(jt::Vector2f const& positionOffset = jt::Vector2f { 0, 0 }) const;

    void setSDLColor(jt::Color const& col) const;
};
} // namespace jt

#endif
