﻿#ifndef GUARD_JAMTEMPLATE_BAR_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_BAR_HPP_INCLUDEGUARD

#include "drawable_impl.hpp"
#include "render_target.hpp"
#include "shape.hpp"
#include <memory>
#include <vector>

namespace jt {

class Bar : public jt::DrawableImpl {
public:
    using Sptr = std::shared_ptr<Bar>;

    Bar(float width, float height, bool horizontal = true);

    void setFrontColor(jt::Color const& col);
    void setBackColor(jt::Color const& col);

    jt::Color getBackColor() const;

    void setCurrentValue(float value);
    float getCurrentValue() const;

    void setMaxValue(float max);
    float getMaxValue() const;

    float getValueFraction() const;

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
    float m_valueMax { 1.0f };
    float m_valueCurrent { 0.0f };

    float const m_width;
    float const m_height;
    bool m_horizontal;

    mutable std::shared_ptr<jt::Shape> m_shapeFull { nullptr };
    std::shared_ptr<jt::Shape> m_shapeProgress { nullptr };

    jt::Color m_flashColor { jt::colors::White };

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