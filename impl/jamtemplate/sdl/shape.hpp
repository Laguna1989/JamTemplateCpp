#ifndef GUARD_JAMTEMPLATE_SHAPE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SHAPE_HPP_INCLUDEGUARD

#include "drawable_impl.hpp"
#include "rect.hpp"
#include "render_target.hpp"
#include "vector.hpp"
#include <SDL2/SDL.h>
#include <memory>

namespace jt {
class Shape : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Shape>;

    void makeRect(jt::Vector2 size);

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setFlashColor(jt::Color const& col) override;
    jt::Color getFlashColor() const override;

    void setPosition(jt::Vector2 const& pos) override;
    jt::Vector2 getPosition() const override;

    // sf::Transform const getTransform() const override { return m_shape->getTransform(); }

    jt::Rect getGlobalBounds() const override;
    jt::Rect getLocalBounds() const override;

    void setScale(jt::Vector2 const& scale) override;
    jt::Vector2 getScale() const override;

    void setOrigin(jt::Vector2 const& origin) override;
    jt::Vector2 getOrigin() const override;

private:
    mutable std::shared_ptr<SDL_Texture> m_text;

    jt::Vector2 m_position { 0, 0 };
    jt::Recti m_sourceRect { 0, 0, 0, 0 };
    jt::Color m_color { jt::colors::White };
    jt::Vector2 m_scale { 1.0f, 1.0f };
    jt::Vector2 m_origin { 0.0f, 0.0f };
    jt::Color m_colorFlash { jt::colors::White };
    jt::Vector2 m_offsetFromOrigin { 0.0f, 0.0f };

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;

    void doUpdate(float /*elapsed*/) override;
    void doRotate(float /*rot*/) override;

    SDL_Rect getDestRect(jt::Vector2 const& positionOffset = jt::Vector2 { 0, 0 }) const;

    void setSDLColor(jt::Color const& col) const;
};
} // namespace jt

#endif
