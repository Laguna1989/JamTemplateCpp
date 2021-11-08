#include "box2d_joint.hpp"

jt::Box2DJoint::Box2DJoint(std::shared_ptr<Box2DWorldInterface> world, const b2JointDef* def)
{
    setB2Joint(world->createJoint(def));
    m_world = world;
}

void jt::Box2DJoint::doDestroy() { m_world->destroyJoint(m_joint); }

void jt::Box2DJoint::setB2Joint(b2Joint* joint) { m_joint = joint; }
