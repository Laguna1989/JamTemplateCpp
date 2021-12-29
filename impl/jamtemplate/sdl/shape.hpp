#ifndef GUARD_JAMTEMPLATE_SHAPE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SHAPE_HPP_INCLUDEGUARD

#include "drawable_impl.hpp"
#include "rect.hpp"
#include "render_target.hpp"
#include "texture_manager_interface.hpp"
#include "vector.hpp"
#include <SDL2/SDL.h>
#include <memory>

namespace jt {
class Shape : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Shape>;

    void makeRect(jt::Vector2f size, jt::TextureManagerInterface& textureManager);
    void makeCircle(float radius, jt::TextureManagerInterface& textureManager);

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setFlashColor(jt::Color const& col) override;
    jt::Color getFlashColor() const override;

    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    void setScale(jt::Vector2f const& scale) override;
    jt::Vector2f getScale() const override;

    void setOrigin(jt::Vector2f const& origin) override;
    jt::Vector2f getOrigin() const override;

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::Vector2f m_position { 0, 0 };
    jt::Recti m_sourceRect { 0, 0, 0, 0 };
    jt::Color m_color { jt::colors::White };
    jt::Vector2f m_scale { 1.0f, 1.0f };
    jt::Vector2f m_origin { 0.0f, 0.0f };
    jt::Color m_colorFlash { jt::colors::White };
    jt::Vector2f m_offsetFromOrigin { 0.0f, 0.0f };

    void doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    void doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    void doUpdate(float /*elapsed*/) override;
    void doRotate(float /*rot*/) override;

    SDL_Rect getDestRect(jt::Vector2f const& positionOffset = jt::Vector2f { 0, 0 }) const;

    void setSDLColor(jt::Color const& col) const;
};
} // namespace jt

#endif
