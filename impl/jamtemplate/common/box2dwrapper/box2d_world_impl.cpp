#include "box2dwrapper/box2d_world_impl.hpp"
#include <box2dwrapper/box2d_contact_manager.hpp>
#include <conversions.hpp>
#include <Box2D/Box2D.h>

jt::Box2DWorldImpl::Box2DWorldImpl(
    jt::Vector2f const& gravity, std::shared_ptr<jt::Box2DContactManagerInterface> contactManager)
    : m_world { std::make_unique<b2World>(jt::Conversion::vec(gravity)) }
    , m_newContactManager { contactManager }
{
    if (m_newContactManager == nullptr) {
        m_newContactManager = std::make_shared<jt::Box2DContactManager>();
    }

    m_world->SetContactListener(m_newContactManager.get());
}

b2Body* jt::Box2DWorldImpl::createBody(b2BodyDef const* definition)
{
    return m_world->CreateBody(definition);
}

void jt::Box2DWorldImpl::destroyBody(b2Body* body) { m_world->DestroyBody(body); }

b2Joint* jt::Box2DWorldImpl::createJoint(b2JointDef const* definition)
{
    return m_world->CreateJoint(definition);
}

void jt::Box2DWorldImpl::destroyJoint(b2Joint* joint) { m_world->DestroyJoint(joint); }

void jt::Box2DWorldImpl::step(float elapsed, int velocityIterations, int positionIterations)
{
    m_world->Step(elapsed, velocityIterations, positionIterations);
}

jt::Box2DContactCallbackRegistryInterface& jt::Box2DWorldImpl::getContactManager()
{
    return *m_newContactManager;
}
