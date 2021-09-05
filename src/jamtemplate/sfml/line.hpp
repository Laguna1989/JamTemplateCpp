#ifndef GUARD_JAMTEMPLATE_LINE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_LINE_HPP_INCLUDEGUARD

#include "vector.hpp"
#include "drawable_impl.hpp"
#include "render_target.hpp"

namespace jt {
class Line : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Line>;
    Line(jt::Vector2 lineVector);

    void setColor(jt::Color const& col) override;
    const jt::Color getColor() const override;
    
    void setPosition(jt::Vector2 const& pos) override;
    const jt::Vector2 getPosition() const override;
    
    jt::Rect const getGlobalBounds() const override;
    jt::Rect const getLocalBounds() const override;

    void setFlashColor(jt::Color const& col) override ;
    const jt::Color getFlashColor() const override ;

    void setScale(jt::Vector2 const& scale) override ;
    const jt::Vector2 getScale() const override ;

    void setOrigin(jt::Vector2 const& origin) override ;
    const jt::Vector2 getOrigin() const override ;
    

private:

    jt::Vector2 m_lineVector;
    jt::Color m_color;
    jt::Vector2 m_position;

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doUpdate(float elapsed) override;
    void doRotate(float d) override;
};

}

#endif // QUASARRUSH_LINE_HPP
