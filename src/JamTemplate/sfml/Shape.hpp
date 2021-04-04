#ifndef GUARD_JAMTEMPLATE_SHAPE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SHAPE_HPP_INCLUDEGUARD

#include "DrawableImpl.hpp"
#include "Rendertarget.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace jt {
class Shape : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Shape>;

    void makeRect(jt::Vector2 size);

    void setColor(jt::Color const& col) override;
    const jt::Color getColor() const override;

    void setFlashColor(jt::Color const& col) override;
    const jt::Color getFlashColor() const override;

    void setPosition(jt::Vector2 const& pos) override;
    const jt::Vector2 getPosition() const override;

    // sf::Transform const getTransform() const override { return m_shape->getTransform(); }
    jt::Rect const getGlobalBounds() const override;
    jt::Rect const getLocalBounds() const override;

    void setScale(jt::Vector2 const& scale) override;
    const jt::Vector2 getScale() const override;

    void setOrigin(jt::Vector2 const& origin) override;
    const jt::Vector2 getOrigin() const override;

    std::shared_ptr<sf::Shape> getShape();

private:
    mutable std::shared_ptr<sf::Shape> m_shape = nullptr;
    std::shared_ptr<sf::Shape> m_flashShape = nullptr;

    jt::Vector2 m_position { 0, 0 };

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doUpdate(float elapsed) override;
    void doRotate(float rot);
};
} // namespace jt

#endif
