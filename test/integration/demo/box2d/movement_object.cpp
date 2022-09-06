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

    handleMovement(elapsed);
}
void Player::handleMovement(float const elapsed)
{
    auto const horizontalAcceleration = 55000.0f;
    auto const maxHorizontalVelocity = 80.0f;
    auto const horizontalDampening = 110.0f;

    auto const jumpInitialVelocity = -140.0f;
    auto const maxVerticalVelocity = 100.0f;
    auto const jumpVerticalAcceleration = -25000.0f;

    bool horizontalMovement { false };
    auto b2b = m_physicsObject->getB2Body();
    auto v = m_physicsObject->getVelocity();
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::D)) {
        if (v.x < 0) {
            v.x *= 0.9f;
        }
        b2b->ApplyForceToCenter(b2Vec2 { horizontalAcceleration, 0 }, true);
        horizontalMovement = true;
    }

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::A)) {
        if (v.x > 0) {
            v.x *= 0.9f;
        }
        b2b->ApplyForceToCenter(b2Vec2 { -horizontalAcceleration, 0 }, true);
        horizontalMovement = true;
    }

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::B)) {
        m_animation->flash(0.5f, jt::colors::Red);
    }

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::W)) {
        v.y = jumpInitialVelocity;
    }
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::W)) {
        if (v.y < 0) {
            std::cout << "reduce gravity\n";
            b2b->ApplyForceToCenter(b2Vec2 { 0, jumpVerticalAcceleration }, true);
        }
    }

    if (v.y >= maxVerticalVelocity) {
        v.y = maxVerticalVelocity;
    }
    // clamp horizontal Velocity
    if (v.x >= maxHorizontalVelocity) {
        v.x = maxHorizontalVelocity;
    } else if (v.x <= -maxHorizontalVelocity) {
        v.x = -maxHorizontalVelocity;
    }

    // damp horizontal movement
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
