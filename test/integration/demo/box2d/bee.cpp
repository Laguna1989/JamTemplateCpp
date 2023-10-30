#include "bee.hpp"
#include <box2d/user_data_entries.hpp>
#include <Box2D/Box2D.h>
#include <stdexcept>

Bee::Bee(std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2f const& position,
    std::shared_ptr<EnemyMovementInterface> movement)
{
    if (movement == nullptr) {
        throw std::invalid_argument { "invalid movement pattern" };
    }
    m_position = position;

    m_movement = movement;

    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_kinematicBody;
    m_physicsObject = std::make_shared<jt::Box2DObject>(world, &bodyDef);
}

void Bee::doCreate()
{
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    b2CircleShape circleCollider {};
    circleCollider.m_radius = 3.5f;
    circleCollider.m_p.Set(3.5f, 3.5f);
    fixtureDef.shape = &circleCollider;
    auto collider = m_physicsObject->getB2Body()->CreateFixture(&fixtureDef);
    m_physicsObject->setPosition(m_position);
    collider->SetUserData((void*)g_userDataEnemyID);

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
