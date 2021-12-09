#ifndef GUARD_JAMTEMPLATE_BOX2DOBJECT_HPP_GUARD
#define GUARD_JAMTEMPLATE_BOX2DOBJECT_HPP_GUARD

#include "box2d_object.hpp"

namespace jt {
Box2DObject::Box2DObject(std::shared_ptr<Box2DWorldInterface> world, b2BodyDef const* def)
{
    setB2Body(world->createBody(def));
    m_world = world;
}

jt::Vector2f Box2DObject::getPosition() const { return Conversion::vec(m_body->GetPosition()); }

void Box2DObject::setPosition(jt::Vector2f const& position)
{
    m_body->SetTransform(Conversion::vec(position), m_body->GetAngle());
}

jt::Vector2f Box2DObject::getVelocity() const
{
    return Conversion::vec(m_body->GetLinearVelocity());
}

void Box2DObject::setVelocity(jt::Vector2f const& v)
{
    m_body->SetLinearVelocity(Conversion::vec(v));
}

float Box2DObject::getRotation() const { return m_body->GetAngle(); }

b2Body* Box2DObject::getB2Body() { return m_body; }

void Box2DObject::setB2Body(b2Body* body) { m_body = body; }

void Box2DObject::doDestroy()
{
    if (m_world.expired()) {
        return;
    }
    m_world.lock()->destroyBody(m_body);
}

} // namespace jt

#endif
