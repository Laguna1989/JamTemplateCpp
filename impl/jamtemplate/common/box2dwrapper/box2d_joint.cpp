#include "box2d_joint.hpp"
#include <stdexcept>

jt::Box2DJoint::Box2DJoint(std::shared_ptr<Box2DWorldInterface> world, Box2DJointDef const& def)
{
    if (!world) [[unlikely]] {
        throw std::invalid_argument { "cannot create joint for nullptr world" };
    }
    m_world = world;
    m_jointId = world->createJoint(def);
}

void jt::Box2DJoint::doDestroy()
{
    if (m_world.expired()) {
        return;
    }
    m_world.lock()->destroyJoint(m_jointId);
    m_jointId = b2_nullJointId;
}

b2JointId jt::Box2DJoint::getJointId() const { return m_jointId; }
