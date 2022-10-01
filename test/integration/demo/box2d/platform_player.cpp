#include "platform_player.hpp"
#include <box2d/user_data_entries.hpp>
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
    fixtureDef.friction = 0.5f;
    b2CircleShape circleCollider {};
    circleCollider.m_radius = 4.0f;
    fixtureDef.shape = &circleCollider;
    auto playerCollider = m_physicsObject->getB2Body()->CreateFixture(&fixtureDef);
    playerCollider->SetUserData((void*)g_userDataPlayerID);

    fixtureDef.isSensor = true;
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(3.0f, 0.2f, b2Vec2(0, 4), 0);
    fixtureDef.shape = &polygonShape;
    auto footSensorFixture = m_physicsObject->getB2Body()->CreateFixture(&fixtureDef);
    footSensorFixture->SetUserData((void*)g_userDataPlayerFeetID);
}

std::shared_ptr<jt::Animation> Player::getAnimation() { return m_animation; }

void Player::doUpdate(float const elapsed)
{
    auto currentPosition = m_physicsObject->getPosition();
    clampPositionToLevelSize(currentPosition);
    m_physicsObject->setPosition(currentPosition);
    m_animation->setPosition(currentPosition);
    updateAnimation(elapsed);
    handleMovement(elapsed);

    if (m_isTouchingGround != m_wasTouchingGroundLastFrame) {
        auto count = 25;
        if (m_wasTouchingGroundLastFrame) {
            count = 10;
        }
        auto ps = m_postJumpParticles.lock();
        if (ps) {
            ps->fire(count, currentPosition + jt::Vector2f { 0.0f, 5.0f });
        }
    }
    m_wasTouchingGroundLastFrame = m_isTouchingGround;

    m_lastTouchedGroundTimer -= elapsed;
    m_lastJumpTimer -= elapsed;
    m_wantsToJumpTimer -= elapsed;
}

void Player::clampPositionToLevelSize(jt::Vector2f& currentPosition) const
{
    if (currentPosition.x < 4) {
        currentPosition.x = 4;
    }
    if (currentPosition.x > m_levelSizeInTiles.x - 4) {
        currentPosition.x = m_levelSizeInTiles.x - 4;
    }
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
    auto const v = m_horizontalMovement ? abs(m_physicsObject->getVelocity().x) / 90.0f : 0.0f;
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
    auto const maxHorizontalVelocity = 90.0f;
    auto const horizontalDampening = 130.0f;

    auto const jumpInitialVelocity = -140.0f;
    auto const maxVerticalVelocity = 100.0f;
    auto const jumpVerticalAcceleration = -9500.0f;

    auto const jumpDeadTime = 0.3f;
    auto const preLandJumpTimeFrame = 0.1f;

    auto b2b = getB2Body();

    m_horizontalMovement = false;

    auto v = m_physicsObject->getVelocity();
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::D)) {
        if (v.x < 0) {
            v.x *= 0.9f;
        }
        b2b->ApplyForceToCenter(b2Vec2 { horizontalAcceleration, 0 }, true);
        m_horizontalMovement = true;
    }

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::A)) {
        if (v.x > 0) {
            v.x *= 0.9f;
        }
        b2b->ApplyForceToCenter(b2Vec2 { -horizontalAcceleration, 0 }, true);
        m_horizontalMovement = true;
    }

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::W)) {
        if (m_wantsToJumpTimer <= 0.0f) {
            m_wantsToJumpTimer = preLandJumpTimeFrame;
        }
    }

    if (m_wantsToJumpTimer >= 0.0f) {
        if (canJump()) {

            m_lastJumpTimer = jumpDeadTime;
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
    if (!m_horizontalMovement) {
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

void Player::setTouchesGround(bool touchingGround)
{
    auto const m_postDropJumpTimeFrame = 0.2f;
    m_isTouchingGround = touchingGround;
    if (m_isTouchingGround) {
        m_lastTouchedGroundTimer = m_postDropJumpTimeFrame;
    }
}

jt::Vector2f Player::getPosOnScreen() const { return m_animation->getScreenPosition(); }

void Player::setPosition(jt::Vector2f const& pos) { m_physicsObject->setPosition(pos); }

jt::Vector2f Player::getPosition() const { return m_physicsObject->getPosition(); }

void Player::setWalkParticleSystem(std::weak_ptr<jt::ParticleSystem<jt::Shape, 50>> ps)
{
    m_walkParticles = ps;
}

void Player::setJumpParticleSystem(std::weak_ptr<jt::ParticleSystem<jt::Shape, 50>> ps)
{
    m_postJumpParticles = ps;
}

void Player::setLevelSize(jt::Vector2f const& levelSizeInTiles)
{
    m_levelSizeInTiles = levelSizeInTiles;
}

bool Player::canJump() const
{
    if (m_lastJumpTimer >= 0.0f) {
        return false;
    }
    if (m_isTouchingGround) {
        return true;
    }
    if (m_lastTouchedGroundTimer > 0) {
        return true;
    }
    return false;
}
