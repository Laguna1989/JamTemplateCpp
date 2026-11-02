#include "bee.hpp"
#include <box2d/collision_categories.hpp>
#include <box2d/box2d.h>
#include <stdexcept>

Bee::Bee(std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2f const& position,
    std::shared_ptr<EnemyMovementInterface> movement)
{
    if (movement == nullptr) {
        throw std::invalid_argument { "invalid movement pattern" };
    }
    m_position = position;

    m_movement = movement;

    auto bodyDef = b2DefaultBodyDef();
    bodyDef.motionLocks.angularZ = true;
    bodyDef.type = b2_kinematicBody;
    m_physicsObject = std::make_shared<jt::Box2DObject>(world, bodyDef);
}

void Bee::doCreate()
{
    auto shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.2f;
    shapeDef.filter.categoryBits = eCategoryEnemy;
    b2Circle const circleCollider { b2Vec2 { 3.5f, 3.5f }, 3.5f };
    b2CreateCircleShape(m_physicsObject->getBodyId(), &shapeDef, &circleCollider);
    m_physicsObject->setPosition(m_position);

    m_anim = std::make_shared<jt::Animation>();
    m_anim->add("assets/test/integration/demo/bee.png", "right", jt::Vector2u { 8u, 8u }, { 0, 1 },
        0.09f, textureManager());
    m_anim->add("assets/test/integration/demo/bee.png", "left", jt::Vector2u { 8u, 8u }, { 2, 3 },
        0.09f, textureManager());
    m_anim->setPosition(jt::Vector2f { 100.0f, 100.0f });
    m_anim->play("left");
}

void Bee::doUpdate(float const elapsed)
{
    m_movement->update(elapsed, m_physicsObject);
    m_anim->setPosition(m_physicsObject->getPosition());
    auto const velocityX = m_physicsObject->getVelocity().x;
    if (velocityX == 0) {
        // TODO make bee look towards player
    } else if (velocityX > 0) {
        m_anim->play("right");
    } else {
        m_anim->play("left");
    }
    m_anim->update(elapsed);
}

void Bee::doDraw() const { m_anim->draw(renderTarget()); }
