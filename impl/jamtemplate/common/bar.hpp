#ifndef GUARD_JAMTEMPLATE_BAR_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_BAR_HPP_INCLUDEGUARD

#include "drawable_impl.hpp"
#include <memory>
#include <vector>

namespace jt {

class Shape;
class TextureManagerInterface;

class Bar : public jt::DrawableImpl {
public:
    using Sptr = std::shared_ptr<Bar>;

    /// Constructor
    ///
    /// \param width  width of the bar
    /// \param height height of the bar
    /// \param horizontal if true, bar is horizontal (left to right), if false (bottom to top)
    Bar(float width, float height, bool horizontal, jt::TextureManagerInterface& textureManager);

    /// Set front color
    ///
    /// \param col the color
    void setFrontColor(jt::Color const& col);

    /// Set back color
    ///
    /// \param col
    void setBackColor(jt::Color const& col);

    jt::Color getBackColor() const;

    /// Set the current value
    ///
    /// \param value the value. Will be cropped to range [0, MaxValue]
    void setCurrentValue(float value);
    float getCurrentValue() const;

    /// Set the maximum value
    ///
    /// \param max the maximum value. If negative, a invalid argument exception will be raised
    void setMaxValue(float max);
    float getMaxValue() const;

    /// Get the Value fraction (current/max)
    ///
    /// \return return (current/max)
    float getValueFraction() const;

    virtual void setColor(jt::Color const& col) override;
    virtual jt::Color getColor() const override;

    virtual void setPosition(jt::Vector2f const& pos) override;
    virtual jt::Vector2f getPosition() const override;

    virtual jt::Rectf getGlobalBounds() const override;
    virtual jt::Rectf getLocalBounds() const override;

    virtual void setFlashColor(jt::Color const& col) override;
    virtual jt::Color getFlashColor() const override;

    virtual void setScale(jt::Vector2f const& scale) override;
    virtual jt::Vector2f getScale() const override;

    virtual void setOrigin(jt::Vector2f const& origin) override;
    virtual jt::Vector2f getOrigin() const override;

private:
    float m_valueMax;
    float m_valueCurrent;

    float const m_width;
    float const m_height;
    bool m_horizontal;

    mutable std::shared_ptr<jt::Shape> m_shapeFull { nullptr };
    std::shared_ptr<jt::Shape> m_shapeProgress { nullptr };

    jt::Color m_flashColor { jt::colors::White };
    float const m_progressYOffsetFraction { 0.1f };

    virtual void doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const override;
    virtual void doDrawFlash(std::shared_ptr<jt::RenderTarget> const sptr) const override;
    virtual void doDrawShadow(std::shared_ptr<jt::RenderTarget> const sptr) const override;

    // overwrite this method:
    // things to take care of:
    //   - make sure flash object and normal object are at the same position
    virtual void doUpdate(float elapsed) override;
    virtual void doFlash(float /*t*/, jt::Color /*col = jt::colors::White*/) override;
    virtual void doRotate(float /*rot*/) override;
};

} // namespace jt

#endif
