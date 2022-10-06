#ifndef JAMTEMPLATE_SHAPE_HPP
#define JAMTEMPLATE_SHAPE_HPP

#include <drawable_impl_sfml.hpp>
#include <render_target.hpp>
#include <texture_manager_interface.hpp>
#include <memory>

namespace sf {
class Shape;
}

namespace jt {
class Shape : public DrawableImplSFML {
public:
    using Sptr = std::shared_ptr<Shape>;

    void makeRect(jt::Vector2f size, TextureManagerInterface&);
    void makeCircle(float radius, TextureManagerInterface&);

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    void setScale(jt::Vector2f const& scale) override;
    jt::Vector2f getScale() const override;

    void setOriginInternal(jt::Vector2f const& origin) override;

private:
    mutable std::shared_ptr<sf::Shape> m_shape = nullptr;
    std::shared_ptr<sf::Shape> m_flashShape = nullptr;

    jt::Vector2f m_position { 0, 0 };

    void doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doUpdate(float elapsed) override;
    void doRotate(float rot) override;
};
} // namespace jt

#endif
