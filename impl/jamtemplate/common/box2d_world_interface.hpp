#ifndef GUARD_JAMTEMPLATE_BOX2DWRAPPER_HPP_GUARD
#define GUARD_JAMTEMPLATE_BOX2DWRAPPER_HPP_GUARD

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

    /// Sets the contact listener for this world. Use this to react to collisions.
    /// \param listener The contact listener to wake up when things collide in the world
    virtual void setContactListener(std::shared_ptr<b2ContactListener> listener) = 0;

    /// step physics simulation forward
    /// \param elapsed elapsed time in seconds
    /// \param velocityIterations number of velocity iterations
    /// \param positionIterations number of position iterations
    virtual void step(float elapsed, int velocityIterations, int positionIterations) = 0;

    /// Destructor
    virtual ~Box2DWorldInterface() = default;
};
} // namespace jt

#endif
