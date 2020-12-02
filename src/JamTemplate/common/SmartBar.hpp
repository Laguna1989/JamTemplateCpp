#ifndef GUARD_JAMTEMPLATE_SMARTBAR_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SMARTBAR_HPP_INCLUDEGUARD

#include "SmartDrawable.hpp"
#include "SmartShape.hpp"
#include "rendertarget.hpp"
#include <cassert>
#include <memory>
#include <vector>

namespace jt {

class SmartBar : public jt::SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartBar>;

    SmartBar(float width, float height);

    void setFrontColor(jt::color const& col);
    void setBackColor(jt::color const& col);

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

    virtual void setColor(jt::color const& col) override;
    virtual const jt::color getColor() const override;

    virtual void setPosition(jt::vector2 const& pos) override;
    virtual const jt::vector2 getPosition() const override;

    // virtual sf::Transform const getTransform() const override;
    virtual jt::rect const getGlobalBounds() const override;
    virtual jt::rect const getLocalBounds() const override;

    virtual void setFlashColor(jt::color const& col) override;
    virtual const jt::color getFlashColor() const override;

    virtual void setScale(jt::vector2 const& scale) override;
    virtual const jt::vector2 getScale() const override;

    virtual void setOrigin(jt::vector2 const& origin) override;
    virtual const jt::vector2 getOrigin() const override;

private:
    float m_valueMax;
    float m_valueCurrent;

    float const m_width;
    float const m_height;

    mutable std::shared_ptr<jt::SmartShape> m_shapeFull;
    std::shared_ptr<jt::SmartShape> m_shapeProgress;

    virtual void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    virtual void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;
    virtual void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;

    // overwrite this method:
    // things to take care of:
    //   - make sure flash object and normal object are at the same position
    virtual void doUpdate(float elapsed) override;
    virtual void doFlash(float /*t*/, jt::color /*col = jt::colors::White*/) override;
    virtual void doRotate(float /*rot*/) override;
};

} // namespace jt

#endif
