#include "box2d_joint.hpp"

jt::Box2DJoint::Box2DJoint(std::shared_ptr<Box2DWorldInterface> world, const b2JointDef* def)
{
    if (!world) {
        throw std::invalid_argument { "cannot create joint for nullptr world" };
    }
    m_world = world;
    setB2Joint(world->createJoint(def));
}

void jt::Box2DJoint::doDestroy()
{
    if (m_world.expired()) {
        return;
    }
    m_world.lock()->destroyJoint(m_joint);
    m_joint = nullptr;
}

void jt::Box2DJoint::setB2Joint(b2Joint* joint) { m_joint = joint; }
b2Joint* jt::Box2DJoint::getB2Joint() const { return m_joint; }
