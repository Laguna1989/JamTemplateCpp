#include "box2d_world_impl.hpp"
#include "Box2D/Box2D.h"
#include "conversions.hpp"

namespace jt {

Box2DWorldImpl::Box2DWorldImpl(jt::Vector2f const& gravity)
    : m_world { std::make_unique<b2World>(jt::Conversion::vec(gravity)) }
{
}

b2Body* Box2DWorldImpl::createBody(b2BodyDef const* defintion)
{
    return m_world->CreateBody(defintion);
}

void Box2DWorldImpl::destroyBody(b2Body* body) { m_world->DestroyBody(body); }

b2Joint* Box2DWorldImpl::createJoint(b2JointDef const* defintion)
{
    return m_world->CreateJoint(defintion);
}

void Box2DWorldImpl::destroyJoint(b2Joint* joint) { m_world->DestroyJoint(joint); }

void Box2DWorldImpl::setContactListener(std::shared_ptr<b2ContactListener> listener)
{
    m_contactListener = listener;
    m_world->SetContactListener(m_contactListener.get());
}

void Box2DWorldImpl::step(float elapsed, int velocityIterations, int positionIterations)
{
    m_world->Step(elapsed, velocityIterations, positionIterations);
}

} // namespace jt
