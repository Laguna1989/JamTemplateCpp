#include "physics_body.hpp"
#include <conversions.hpp>
#include <drawable_helpers.hpp>
#include <random/random.hpp>

PhysicsBody::PhysicsBody(
    std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2f const& position)
{
    auto bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = jt::Conversion::vec(position);
    bodyDef.linearVelocity = jt::Conversion::vec(jt::Random::getRandomPointInCircle(100.0f));
    bodyDef.angularVelocity = jt::Random::getFloat(-2.0f, 2.0f);
    m_physicsObject = std::make_shared<jt::Box2DObject>(world, bodyDef);
}

PhysicsBody* PhysicsBody::fromShape(b2ShapeId const shapeId)
{
    return static_cast<PhysicsBody*>(b2Body_GetUserData(b2Shape_GetBody(shapeId)));
}

void PhysicsBody::doCreate()
{
    auto const bodyId = m_physicsObject->getBodyId();
    b2Body_SetUserData(bodyId, this);

    m_color = jt::Random::getRandomColorHSV(0.0f, 359.0f, 40.0f, 60.0f, 70.0f, 90.0f);

    auto shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = 0.0f;
    shapeDef.material.restitution = 1.0f;
    // required for the contact events that trigger flash()
    shapeDef.enableContactEvents = true;

    if (jt::Random::getChance()) {
        auto const radius = jt::Random::getFloat(6.0f, 14.0f);
        b2Circle const circle { b2Vec2 { 0.0f, 0.0f }, radius };
        b2CreateCircleShape(bodyId, &shapeDef, &circle);
        m_shape = jt::dh::createShapeCircle(radius, m_color, textureManager());
    } else {
        jt::Vector2f const halfSize { jt::Random::getFloat(5.0f, 14.0f),
            jt::Random::getFloat(5.0f, 14.0f) };
        auto const box = b2MakeBox(halfSize.x, halfSize.y);
        b2CreatePolygonShape(bodyId, &shapeDef, &box);
        m_shape = jt::dh::createShapeRect(halfSize * 2.0f, m_color, textureManager());
    }
    m_shape->setOrigin(jt::OriginMode::CENTER);
}

void PhysicsBody::doUpdate(float const elapsed)
{
    m_shape->setColor(m_highlightColor.value_or(m_color));
    m_shape->setPosition(m_physicsObject->getPosition());
    m_shape->setRotation(m_physicsObject->getRotation());
    m_shape->update(elapsed);
}

void PhysicsBody::doDraw() const { m_shape->draw(renderTarget()); }

void PhysicsBody::flash() { m_shape->flash(0.2f, jt::colors::White); }

void PhysicsBody::setHighlightColor(std::optional<jt::Color> const& color)
{
    m_highlightColor = color;
}

std::string PhysicsBody::getName() const { return "PhysicsBody"; }
