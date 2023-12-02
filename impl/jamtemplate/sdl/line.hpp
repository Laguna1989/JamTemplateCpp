#ifndef JAMTEMPLATE_LINE_HPP
#define JAMTEMPLATE_LINE_HPP

#include <drawable_impl_sdl.hpp>
#include <render_target_layer.hpp>
#include <vector.hpp>

namespace jt {
class Line : public DrawableImplSdl {
public:
    using Sptr = std::shared_ptr<Line>;

    /// Constructor
    Line();

    /// Constructor
    /// \param lineVector the vector from start to end of the line
    explicit Line(jt::Vector2f lineVector);

    /// Set line Vector from start to end of the line
    /// \param lineVector line vector
    void setLineVector(jt::Vector2f const& lineVector) noexcept;

    /// Get line Vector from start to end of the line
    /// \return line vector
    jt::Vector2f getLineVector() const noexcept;

    void setColor(jt::Color const& col) noexcept override;
    jt::Color getColor() const noexcept override;

    void setPosition(jt::Vector2f const& pos) noexcept override;
    jt::Vector2f getPosition() const noexcept override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    void setScale(jt::Vector2f const& scale) override;
    jt::Vector2f getScale() const override;

private:
    jt::Vector2f m_lineVector;
    jt::Color m_color;
    jt::Vector2f m_position;

    jt::Vector2f m_origin;

    void doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doUpdate(float elapsed) noexcept override;
    void doRotate(float d) noexcept override;
};

} // namespace jt

#endif // JAMTEMPLATE_LINE_HPP
