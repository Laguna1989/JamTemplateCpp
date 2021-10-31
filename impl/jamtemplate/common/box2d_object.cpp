#include "box2d_object.hpp"

namespace jt {
Box2DObject::Box2DObject(std::shared_ptr<Box2DWorldInterface> world, b2BodyDef const* def)
{
    setB2Body(world->createBody(def));
    m_world = world;
}

jt::Vector2 Box2DObject::getPosition() const { return Conversion::vec(m_body->GetPosition()); }

void Box2DObject::setPosition(jt::Vector2 const& position)
{
    m_body->SetTransform(Conversion::vec(position), m_body->GetAngle());
}

jt::Vector2 Box2DObject::getVelocity() const
{
    return Conversion::vec(m_body->GetLinearVelocity());
}

void Box2DObject::setVelocity(jt::Vector2 const& v)
{
    m_body->SetLinearVelocity(Conversion::vec(v));
}

float Box2DObject::getRotation() const { return m_body->GetAngle(); }

b2Body* Box2DObject::getB2Body() { return m_body; }

void Box2DObject::doDestroy() { m_world->destroyBody(m_body); }

void Box2DObject::setB2Body(b2Body* body) { m_body = body; }
} // namespace jt
