#ifndef DEMO_COLLISION_PHYSICS_BODY_HPP
#define DEMO_COLLISION_PHYSICS_BODY_HPP

#include <box2dwrapper/box2d_object.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <color/color.hpp>
#include <game_object.hpp>
#include <shape.hpp>
#include <vector.hpp>
#include <memory>
#include <optional>

/// Dynamic Box2D body with a random circle or box collider and a matching shape.
/// The Box2D user data of the body points to this object, see fromShape().
class PhysicsBody : public jt::GameObject {
public:
    PhysicsBody(std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2f const& position);

    /// Get the PhysicsBody that owns a Box2D shape
    /// \param shapeId the Box2D shape
    /// \return the PhysicsBody or nullptr if the shape does not belong to a PhysicsBody (e.g. walls)
    static PhysicsBody* fromShape(b2ShapeId shapeId);

    /// Briefly flash the body, e.g. on contact
    void flash();

    /// Override the body color until the highlight is cleared again
    /// \param color the highlight color or std::nullopt to show the default color
    void setHighlightColor(std::optional<jt::Color> const& color);

    std::string getName() const override;

private:
    std::shared_ptr<jt::Box2DObject> m_physicsObject { nullptr };
    std::shared_ptr<jt::Shape> m_shape { nullptr };
    jt::Color m_color {};
    std::optional<jt::Color> m_highlightColor {};

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // DEMO_COLLISION_PHYSICS_BODY_HPP
