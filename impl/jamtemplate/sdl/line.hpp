#ifndef GUARD_JAMTEMPLATE_LINE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_LINE_HPP_INCLUDEGUARD

#include "drawable_impl.hpp"
#include "render_target.hpp"
#include "vector.hpp"

namespace jt {
class Line : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Line>;
    Line(jt::Vector2 lineVector);

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setPosition(jt::Vector2 const& pos) override;
    jt::Vector2 getPosition() const override;

    jt::Rect getGlobalBounds() const override;
    jt::Rect getLocalBounds() const override;

    void setFlashColor(jt::Color const& col) override;
    jt::Color getFlashColor() const override;

    void setScale(jt::Vector2 const& scale) override;
    jt::Vector2 getScale() const override;

    void setOrigin(jt::Vector2 const& origin) override;
    jt::Vector2 getOrigin() const override;

private:
    jt::Vector2 m_lineVector;
    jt::Color m_color;
    jt::Vector2 m_position;

    jt::Color m_flashColor { jt::colors::White };
    Vector2 m_origin;
    Vector2 m_scale { 1.0f, 1.0f };

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doUpdate(float elapsed) override;
    void doRotate(float d) override;
};

} // namespace jt

#endif // QUASARRUSH_LINE_HPP
