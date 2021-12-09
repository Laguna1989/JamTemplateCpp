#ifndef GUARD_JAMTEMAPLTE_BOX2D_WORLD_IMPL_HPP
#define GUARD_JAMTEMAPLTE_BOX2D_WORLD_IMPL_HPP

#include "box2d_world_interface.hpp"
#include "vector.hpp"
#include <Box2D/Dynamics/b2World.h>
#include <memory>

namespace jt {

/// Implementation of the Box2DWorldInterface
class Box2DWorldImpl : public Box2DWorldInterface {
public:
    Box2DWorldImpl(jt::Vector2f const& gravity);

    b2Body* createBody(const b2BodyDef* defintion) override;

    void destroyBody(b2Body* body) override;

    b2Joint* createJoint(const b2JointDef* defintion) override;

    void destroyJoint(b2Joint* joint) override;

    void setContactListener(std::shared_ptr<b2ContactListener> listener) override;

    void step(float elapsed, int velocityIterations, int positionIterations) override;

private:
    std::unique_ptr<b2World> m_world;
    std::shared_ptr<b2ContactListener> m_contactListener;
};

} // namespace jt
// namespace jt
#endif // GUARD_JAMTEMAPLTE_BOX2D_WORLD_IMPL_HPP
