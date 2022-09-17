#include "PlatformPlayer.hpp"
#include <game_interface.hpp>
#include <math_helper.hpp>

Player::Player(std::shared_ptr<jt::Box2DWorldInterface> world)
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;

    m_physicsObject = std::make_shared<jt::Box2DObject>(world, &bodyDef);
}

void Player::doCreate()
{
    m_animation = std::make_shared<jt::Animation>();

    m_animation->loadFromJson("assets/test/integration/demo/hero_8x8.json", textureManager());
    m_animation->play("right");
    m_animation->setOffset(jt::OffsetMode::CENTER);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    b2CircleShape circleCollider {};
    circleCollider.m_radius = 4.0f;
    fixtureDef.shape = &circleCollider;
    m_physicsObject->getB2Body()->CreateFixture(&fixtureDef);

    fixtureDef.isSensor = true;
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(2.0f, 0.3f, b2Vec2(0, 4), 0);
    fixtureDef.isSensor = true;
    fixtureDef.shape = &polygonShape;
    b2Fixture* footSensorFixture = m_physicsObject->getB2Body()->CreateFixture(&fixtureDef);
    footSensorFixture->SetUserData((void*)std::uint64_t { 3U });
}

std::shared_ptr<jt::Animation> Player::getAnimation() { return m_animation; }

void Player::doUpdate(float const elapsed)
{

    m_animation->setPosition(m_physicsObject->getPosition());
    updateAnimation(elapsed);
    handleMovement(elapsed);
}

void Player::updateAnimation(float elapsed)
{
    if (m_physicsObject->getVelocity().x > 0) {
        m_animation->play("right");
        m_isMoving = true;
    } else if (m_physicsObject->getVelocity().x < 0) {
        m_animation->play("left");
        m_isMoving = true;
    } else {
        m_isMoving = false;
    }
    auto const v = abs(m_physicsObject->getVelocity().x) / 80.0f;
    m_animation->setAnimationSpeedFactor(v);
    m_animation->update(elapsed);

    m_walkParticlesTimer -= elapsed * v;
    if (m_walkParticlesTimer <= 0) {
        m_walkParticlesTimer = 0.15f;
        if (m_isMoving && m_isTouchingGround) {
            auto ps = m_walkParticles.lock();
            if (ps) {
                ps->fire(1, getPosition());
            }
        }
    }
}

void Player::handleMovement(float const elapsed)
{
    auto const horizontalAcceleration = 15000.0f;
    auto const maxHorizontalVelocity = 80.0f;
    auto const horizontalDampening = 130.0f;

    auto const jumpInitialVelocity = -140.0f;
    auto const maxVerticalVelocity = 100.0f;
    auto const jumpVerticalAcceleration = -5000.0f;

    bool horizontalMovement { false };
    auto b2b = getB2Body();

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

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::W)) {
        if (m_isTouchingGround) {
            v.y = jumpInitialVelocity;
        }
    }
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::W)) {
        if (v.y < 0) {
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
            if (v.x < 0) {
                v.x = 0;
            }
        } else if (v.x < 0) {
            v.x += horizontalDampening * elapsed;
            if (v.x > 0) {
                v.x = 0;
            }
        }
    }

    m_physicsObject->setVelocity(v);
}
b2Body* Player::getB2Body() { return m_physicsObject->getB2Body(); }

void Player::doDraw() const { m_animation->draw(renderTarget()); }
void Player::setTouchesGround(bool touchingGround) { m_isTouchingGround = touchingGround; }
jt::Vector2f Player::getPosOnScreen() const { return m_animation->getScreenPosition(); }
void Player::setPosition(jt::Vector2f const& pos) { m_physicsObject->setPosition(pos); }
jt::Vector2f Player::getPosition() const { return m_physicsObject->getPosition(); }

void Player::setWalkParticleSystem(std::weak_ptr<jt::ParticleSystem<jt::Shape, 50>> ps)
{
    m_walkParticles = ps;
}
