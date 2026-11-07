#pragma once

#include <box2d/box2d.h>
#include <variant>

namespace jt {

/// All joint definitions that can be passed to Box2DWorldInterface::createJoint.
using Box2DJointDef = std::variant<b2DistanceJointDef, b2FilterJointDef, b2MotorJointDef,
    b2PrismaticJointDef, b2RevoluteJointDef, b2WeldJointDef, b2WheelJointDef>;

/// Interface for a box2d world
class Box2DWorldInterface {
public:
    /// Create a physics body
    /// \param definition the definition describing the body. Start from b2DefaultBodyDef().
    /// \return the id of the created body
    virtual b2BodyId createBody(b2BodyDef const& definition) = 0;

    /// Destroy a physics body. Joints attached to the body are destroyed as well.
    /// Destroying an already destroyed body has no effect.
    /// \param body id of the body to be destroyed
    virtual void destroyBody(b2BodyId body) = 0;

    /// Create a Box2D joint
    /// \param definition the definition describing the joint. Start from b2Default*JointDef().
    /// \return the id of the created joint
    virtual b2JointId createJoint(Box2DJointDef const& definition) = 0;

    /// Destroy a Box2D joint. Destroying an already destroyed joint has no effect.
    /// \param joint id of the joint to be destroyed
    virtual void destroyJoint(b2JointId joint) = 0;

    /// Step physics simulation forward
    /// \param elapsed elapsed time in seconds
    /// \param subStepCount number of sub-steps. 4 is a good default.
    virtual void step(float elapsed, int subStepCount) = 0;

    /// Contact events of the last step. Only shapes with enableContactEvents report events.
    /// The returned data is valid until the next call to step.
    /// \return the contact events
    virtual b2ContactEvents getContactEvents() const = 0;

    /// Sensor events of the last step. Both the sensor shape and the visitor shape need
    /// enableSensorEvents. The returned data is valid until the next call to step.
    /// \return the sensor events
    virtual b2SensorEvents getSensorEvents() const = 0;

    /// Get the low level world id, e.g. for queries and ray casts.
    /// \return the world id
    virtual b2WorldId getWorldId() const = 0;

    virtual ~Box2DWorldInterface() = default;
    // avoid slicing
    Box2DWorldInterface(Box2DWorldInterface const&) = delete;
    Box2DWorldInterface(Box2DWorldInterface&&) = delete;
    Box2DWorldInterface& operator=(Box2DWorldInterface const&) = delete;
    Box2DWorldInterface& operator=(Box2DWorldInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    Box2DWorldInterface() = default;
};
} // namespace jt
