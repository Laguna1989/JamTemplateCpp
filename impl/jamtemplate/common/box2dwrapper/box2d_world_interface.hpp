#ifndef JAMTEMPLATE_BOX2DWRAPPER_HPP
#define JAMTEMPLATE_BOX2DWRAPPER_HPP

#include <box2dwrapper/box2d_contact_callback_registry_interface.hpp>
#include <memory>

class b2Body;
struct b2BodyDef;
class b2Joint;
struct b2JointDef;
class b2ContactListener;

namespace jt {

/// Interface for box2World
class Box2DWorldInterface {
public:
    /// Create a physics body
    /// \param definition the definition describing the body
    /// \return the created body
    virtual b2Body* createBody(const b2BodyDef* definition) = 0;

    /// Destroy a physics body
    /// \param body pointer to the body to be destroyed
    virtual void destroyBody(b2Body* body) = 0;

    /// Create a Box2D joint
    /// \param defintion The definition describing the joint
    /// \return The created joint
    virtual b2Joint* createJoint(const b2JointDef* defintion) = 0;

    /// Destory a Box2D joint
    /// \param joint Pointer to the joint to be destroyed
    virtual void destroyJoint(b2Joint* joint) = 0;

    /// Get the ContactManager. This can be used to register/unregister contact callbacks.
    /// \return the ContactManager
    virtual jt::Box2DContactCallbackRegistryInterface& getContactManager() = 0;

    /// Step physics simulation forward
    /// \param elapsed elapsed time in seconds
    /// \param velocityIterations number of velocity iterations
    /// \param positionIterations number of position iterations
    virtual void step(float elapsed, int velocityIterations, int positionIterations) = 0;

    virtual ~Box2DWorldInterface() = default;
    // avoid slicing
    Box2DWorldInterface(const Box2DWorldInterface&) = delete;
    Box2DWorldInterface(Box2DWorldInterface&&) = delete;
    Box2DWorldInterface& operator=(const Box2DWorldInterface&) = delete;
    Box2DWorldInterface& operator=(Box2DWorldInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    Box2DWorldInterface() = default;
};
} // namespace jt

#endif
