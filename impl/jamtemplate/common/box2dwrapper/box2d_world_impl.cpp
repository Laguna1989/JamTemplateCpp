#include "box2d_world_impl.hpp"
#include <conversions.hpp>

namespace {

b2JointId createJointFromDef(b2WorldId const world, b2DistanceJointDef const& def)
{
    return b2CreateDistanceJoint(world, &def);
}

b2JointId createJointFromDef(b2WorldId const world, b2FilterJointDef const& def)
{
    return b2CreateFilterJoint(world, &def);
}

b2JointId createJointFromDef(b2WorldId const world, b2MotorJointDef const& def)
{
    return b2CreateMotorJoint(world, &def);
}

b2JointId createJointFromDef(b2WorldId const world, b2PrismaticJointDef const& def)
{
    return b2CreatePrismaticJoint(world, &def);
}

b2JointId createJointFromDef(b2WorldId const world, b2RevoluteJointDef const& def)
{
    return b2CreateRevoluteJoint(world, &def);
}

b2JointId createJointFromDef(b2WorldId const world, b2WeldJointDef const& def)
{
    return b2CreateWeldJoint(world, &def);
}

b2JointId createJointFromDef(b2WorldId const world, b2WheelJointDef const& def)
{
    return b2CreateWheelJoint(world, &def);
}

b2WorldDef makeWorldDef(jt::Vector2f const& gravity)
{
    auto worldDef = b2DefaultWorldDef();
    worldDef.gravity = jt::Conversion::vec(gravity);
    return worldDef;
}

} // namespace

jt::Box2DWorldImpl::Box2DWorldImpl(jt::Vector2f const& gravity)
    : Box2DWorldImpl { makeWorldDef(gravity) }
{
}

jt::Box2DWorldImpl::Box2DWorldImpl(b2WorldDef const& worldDef)
    : m_worldId { b2CreateWorld(&worldDef) }
{
}

jt::Box2DWorldImpl::~Box2DWorldImpl() { b2DestroyWorld(m_worldId); }

b2BodyId jt::Box2DWorldImpl::createBody(b2BodyDef const& definition)
{
    return b2CreateBody(m_worldId, &definition);
}

void jt::Box2DWorldImpl::destroyBody(b2BodyId const body)
{
    if (b2Body_IsValid(body)) {
        b2DestroyBody(body);
    }
}

b2JointId jt::Box2DWorldImpl::createJoint(Box2DJointDef const& definition)
{
    return std::visit(
        [this](auto const& def) { return createJointFromDef(m_worldId, def); }, definition);
}

void jt::Box2DWorldImpl::destroyJoint(b2JointId joint)
{
    // joints are destroyed implicitly together with their bodies
    if (b2Joint_IsValid(joint)) {
        b2DestroyJoint(joint);
    }
}

void jt::Box2DWorldImpl::step(float const elapsed, int const subStepCount)
{
    b2World_Step(m_worldId, elapsed, subStepCount);
}

b2ContactEvents jt::Box2DWorldImpl::getContactEvents() const
{
    return b2World_GetContactEvents(m_worldId);
}

b2SensorEvents jt::Box2DWorldImpl::getSensorEvents() const
{
    return b2World_GetSensorEvents(m_worldId);
}

b2WorldId jt::Box2DWorldImpl::getWorldId() const { return m_worldId; }
