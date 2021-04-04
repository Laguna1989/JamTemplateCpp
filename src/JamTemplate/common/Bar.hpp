#ifndef GUARD_JAMTEMPLATE_BAR_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_BAR_HPP_INCLUDEGUARD

#include "DrawableImpl.hpp"
#include "Rendertarget.hpp"
#include "Shape.hpp"
#include <cassert>
#include <memory>
#include <vector>

namespace jt {

class Bar : public jt::DrawableImpl {
public:
    using Sptr = std::shared_ptr<Bar>;

    Bar(float width, float height);

    void setFrontColor(jt::Color const& col);
    void setBackColor(jt::Color const& col);

    void setCurrentValue(float position)
    {
        m_valueCurrent = position;
        if (m_valueCurrent < 0) {
            m_valueCurrent = 0;
        } else if (m_valueCurrent > m_valueMax) {
            m_valueCurrent = m_valueMax;
        }
    }

    void setMaxValue(float max)
    {
        assert(max >= 0);
        m_valueMax = max;
    }

    virtual void setColor(jt::Color const& col) override;
    virtual const jt::Color getColor() const override;

    virtual void setPosition(jt::Vector2 const& pos) override;
    virtual const jt::Vector2 getPosition() const override;

    // virtual sf::Transform const getTransform() const override;
    virtual jt::Rect const getGlobalBounds() const override;
    virtual jt::Rect const getLocalBounds() const override;

    virtual void setFlashColor(jt::Color const& col) override;
    virtual const jt::Color getFlashColor() const override;

    virtual void setScale(jt::Vector2 const& scale) override;
    virtual const jt::Vector2 getScale() const override;

    virtual void setOrigin(jt::Vector2 const& origin) override;
    virtual const jt::Vector2 getOrigin() const override;

private:
    float m_valueMax;
    float m_valueCurrent;

    float const m_width;
    float const m_height;

    mutable std::shared_ptr<jt::Shape> m_shapeFull;
    std::shared_ptr<jt::Shape> m_shapeProgress;

    virtual void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    virtual void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;
    virtual void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;

    // overwrite this method:
    // things to take care of:
    //   - make sure flash object and normal object are at the same position
    virtual void doUpdate(float elapsed) override;
    virtual void doFlash(float /*t*/, jt::Color /*col = jt::colors::White*/) override;
    virtual void doRotate(float /*rot*/) override;
};

} // namespace jt

#endif
