#include "box2dwrapper/box2d_world_impl.hpp"
#include <conversions.hpp>
#include <Box2D/Box2D.h>

jt::Box2DWorldImpl::Box2DWorldImpl(jt::Vector2f const& gravity)
    : m_world { std::make_unique<b2World>(jt::Conversion::vec(gravity)) }
{
}

b2Body* jt::Box2DWorldImpl::createBody(b2BodyDef const* defintion)
{
    return m_world->CreateBody(defintion);
}

void jt::Box2DWorldImpl::destroyBody(b2Body* body) { m_world->DestroyBody(body); }

b2Joint* jt::Box2DWorldImpl::createJoint(b2JointDef const* defintion)
{
    return m_world->CreateJoint(defintion);
}

void jt::Box2DWorldImpl::destroyJoint(b2Joint* joint) { m_world->DestroyJoint(joint); }

void jt::Box2DWorldImpl::setContactListener(std::shared_ptr<b2ContactListener> listener)
{
    m_contactListener = listener;
    m_world->SetContactListener(m_contactListener.get());
}

void jt::Box2DWorldImpl::step(float elapsed, int velocityIterations, int positionIterations)
{
    m_world->Step(elapsed, velocityIterations, positionIterations);
}
