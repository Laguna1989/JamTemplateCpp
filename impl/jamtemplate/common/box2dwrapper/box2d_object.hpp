#pragma once

#include <box2dwrapper/box2d_world_interface.hpp>
#include <vector.hpp>
#include <memory>

namespace jt {

/// RAII type Wrapper for a box2d body
class Box2DObject {
public:
    using Sptr = std::shared_ptr<Box2DObject>;
    Box2DObject() = delete;

    /// Constructor
    ///
    /// \param world shared pointer to the world. Only a weak pointer will be stored.
    /// \param def body definition. Start from b2DefaultBodyDef().
    Box2DObject(std::shared_ptr<Box2DWorldInterface> world, b2BodyDef const& def);

    virtual ~Box2DObject();

    // the body is owned exclusively by this object
    Box2DObject(Box2DObject const&) = delete;
    Box2DObject(Box2DObject&&) = delete;
    Box2DObject& operator=(Box2DObject const&) = delete;
    Box2DObject& operator=(Box2DObject&&) = delete;

    /// Get position
    /// \return position
    jt::Vector2f getPosition() const;

    /// Set position (overwrite box2d simulation)
    /// \param position new position
    void setPosition(jt::Vector2f const& position);

    /// Get velocity
    /// \return velocity
    jt::Vector2f getVelocity() const;

    /// Set velocity (overwrite box2d simulation)
    /// \param v new velocity
    void setVelocity(jt::Vector2f const& v);

    /// Add velocity (overwrite box2d simulation)
    /// \param v velocity to be added
    void addVelocity(jt::Vector2f const& v);

    /// Add Force to center
    /// \param f force
    void addForceToCenter(Vector2f const& f);

    /// Get rotation in degree
    /// \return rotation in degree
    float getRotation() const;

    /// Enable or disable the body. A disabled body does not take part in the simulation.
    /// \param enabled true to enable, false to disable
    void setEnabled(bool enabled);

    /// Get the low level Box2d body id, e.g. for attaching shapes
    /// \return the body id
    b2BodyId getBodyId() const;

private:
    b2BodyId m_bodyId { b2_nullBodyId };

    std::weak_ptr<Box2DWorldInterface> m_world;
};

} // namespace jt
