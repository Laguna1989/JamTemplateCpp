#include "box2d_object.hpp"
#include <conversions.hpp>
#include <math_helper.hpp>
#include <stdexcept>

jt::Box2DObject::Box2DObject(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const& def)
{
    if (!world) [[unlikely]] {
        throw std::invalid_argument { "cannot create object for nullptr world" };
    }
    m_bodyId = world->createBody(def);
    m_world = world;
}

jt::Box2DObject::~Box2DObject()
{
    if (m_world.expired()) {
        return;
    }
    m_world.lock()->destroyBody(m_bodyId);
}

jt::Vector2f jt::Box2DObject::getPosition() const
{
    return Conversion::vec(b2Body_GetPosition(m_bodyId));
}

void jt::Box2DObject::setPosition(jt::Vector2f const& position)
{
    b2Body_SetTransform(m_bodyId, Conversion::vec(position), b2Body_GetRotation(m_bodyId));
}

jt::Vector2f jt::Box2DObject::getVelocity() const
{
    return Conversion::vec(b2Body_GetLinearVelocity(m_bodyId));
}

void jt::Box2DObject::setVelocity(jt::Vector2f const& v)
{
    b2Body_SetLinearVelocity(m_bodyId, Conversion::vec(v));
}

void jt::Box2DObject::addVelocity(jt::Vector2f const& v) { setVelocity(getVelocity() + v); }

void jt::Box2DObject::addForceToCenter(jt::Vector2f const& f)
{
    b2Body_ApplyForceToCenter(m_bodyId, Conversion::vec(f), true);
}

float jt::Box2DObject::getRotation() const
{
    return jt::MathHelper::rad2deg(b2Rot_GetAngle(b2Body_GetRotation(m_bodyId)));
}

void jt::Box2DObject::setEnabled(bool const enabled)
{
    if (enabled) {
        b2Body_Enable(m_bodyId);
    } else {
        b2Body_Disable(m_bodyId);
    }
}

b2BodyId jt::Box2DObject::getBodyId() const { return m_bodyId; }
