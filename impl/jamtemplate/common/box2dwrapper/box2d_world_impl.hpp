#pragma once

#include <box2dwrapper/box2d_world_interface.hpp>
#include <vector.hpp>

namespace jt {

/// Implementation of the Box2DWorldInterface. Owns the box2d world.
class Box2DWorldImpl : public Box2DWorldInterface {
public:
    /// Create a world with default settings and the given gravity
    /// \param gravity gravity vector
    explicit Box2DWorldImpl(jt::Vector2f const& gravity);

    /// Create a world with full control over all settings
    /// \param worldDef the world definition. Start from b2DefaultWorldDef().
    explicit Box2DWorldImpl(b2WorldDef const& worldDef);

    ~Box2DWorldImpl() override;

    b2BodyId createBody(b2BodyDef const& definition) override;

    void destroyBody(b2BodyId body) override;

    b2JointId createJoint(Box2DJointDef const& definition) override;

    void destroyJoint(b2JointId joint) override;

    void step(float elapsed, int subStepCount) override;

    b2ContactEvents getContactEvents() const override;

    b2SensorEvents getSensorEvents() const override;

    b2WorldId getWorldId() const override;

private:
    b2WorldId m_worldId { b2_nullWorldId };
};

} // namespace jt
