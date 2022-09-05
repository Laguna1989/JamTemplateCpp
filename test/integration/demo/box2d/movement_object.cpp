#include "movement_object.hpp"
#include <conversions.hpp>
#include <game_interface.hpp>
#include <math_helper.hpp>

Player::Player(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
{
    m_physicsObject = std::make_shared<jt::Box2DObject>(world, def);
}

void Player::doCreate()
{
    m_animation = std::make_shared<jt::Animation>();

    m_animation->add("assets/test/integration/demo/hero_8x8.png", "walk", jt::Vector2u { 8, 8 },
        { 0, 1 }, 0.23f, textureManager());
    m_animation->play("walk");
    //    m_animation->setOffset(jt::OffsetMode::CENTER);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    b2CircleShape circleCollider {};
    circleCollider.m_radius = 8.0f;
    fixtureDef.shape = &circleCollider;
    m_physicsObject->getB2Body()->CreateFixture(&fixtureDef);
}

std::shared_ptr<jt::Animation> Player::getAnimation() { return m_animation; }

void Player::doUpdate(float const elapsed)
{
    using namespace jt::Conversion;
    m_animation->setPosition(vec(m_physicsObject->getB2Body()->GetPosition()));

    m_animation->update(elapsed);
    auto b2b = m_physicsObject->getB2Body();

    bool horizontalMovement { false };
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::D)) {
        b2b->ApplyForceToCenter(b2Vec2 { 60000, 0 }, true);
        horizontalMovement = true;
    }

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::A)) {
        b2b->ApplyForceToCenter(b2Vec2 { -60000, 0 }, true);
        horizontalMovement = true;
    }

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::B)) {
        m_animation->flash(0.5f, jt::colors::Red);
    }

    auto v = m_physicsObject->getVelocity();
    // clamp horizontal Velocity
    float const maxHorizontalVelocity = 70.0f;
    if (v.x >= maxHorizontalVelocity) {
        v.x = maxHorizontalVelocity;
    } else if (v.x <= -maxHorizontalVelocity) {
        v.x = -maxHorizontalVelocity;
    }

    float const horizontalDampening { 100.0f };
    if (!horizontalMovement) {
        if (v.x > 0) {
            v.x -= horizontalDampening * elapsed;
        } else if (v.x < 0) {
            v.x += horizontalDampening * elapsed;
        }
    }

    m_physicsObject->setVelocity(v);
}

void Player::doDraw() const { m_animation->draw(renderTarget()); }
