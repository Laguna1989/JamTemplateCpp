#include "moving_platform.hpp"
#include <math_helper.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

MovingPlatform::MovingPlatform(std::shared_ptr<jt::Box2DWorldInterface> world,
    jt::Vector2f const& size, std::vector<std::pair<jt::Vector2f, float>> const& positions,
    float velocity, float timeoffset)
{
    m_platformSize = size;
    m_positions = positions;
    m_velocity = velocity;
    m_timeOffset = timeoffset;

    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_kinematicBody;
    m_physicsObject = std::make_shared<jt::Box2DObject>(world, &bodyDef);
}

void MovingPlatform::doCreate()
{
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f;
    b2PolygonShape collider {};
    collider.SetAsBox(m_platformSize.x / 2.0f, m_platformSize.y / 2.0f,
        b2Vec2(m_platformSize.x / 2.0f, m_platformSize.y / 2.0f), 0);
    fixtureDef.shape = &collider;
    m_physicsObject->getB2Body()->CreateFixture(&fixtureDef);

    auto const p1 = m_positions[m_currentIndex].first;

    auto const p2 = m_positions[m_currentIndex + 1].first;

    auto const totalDiff = p2 - p1;
    auto diff = totalDiff;
    jt::MathHelper::normalizeMe(diff);
    m_currentVelocity = diff * m_velocity;

    m_timeTilNextPlatform = jt::MathHelper::qlength(totalDiff) / m_velocity;
    m_physicsObject->setPosition(p1);
    //    m_physicsObject->setVelocity(m_currentVelocity);

    m_spriteL = std::make_shared<jt::Sprite>(
        "assets/test/integration/demo/platform_l.png", textureManager());
    m_spriteM = std::make_shared<jt::Sprite>(
        "assets/test/integration/demo/platform_m.png", textureManager());
    m_spriteR = std::make_shared<jt::Sprite>(
        "assets/test/integration/demo/platform_r.png", textureManager());
}

bool MovingPlatform::moveFromTo(
    std::pair<jt::Vector2f, float> from, std::pair<jt::Vector2f, float> to, float elapsed)
{
    if (m_waitTime <= from.second) {
        m_waitTime += elapsed;
        m_physicsObject->setVelocity(jt::Vector2f { 0.0f, 0.0f });
        return false;
    }
    auto const p1 = from.first;
    auto const p2 = to.first;

    auto const totalDiff = p2 - p1;
    auto diff = totalDiff;
    jt::MathHelper::normalizeMe(diff);
    m_currentVelocity = diff * m_velocity;

    m_timeTilNextPlatform = jt::MathHelper::qlength(totalDiff) / m_velocity;
    m_physicsObject->setPosition(p1);

    m_physicsObject->setVelocity(m_currentVelocity);
    return true;
}

void MovingPlatform::doUpdate(float const elapsed)
{
    m_timeOffset -= elapsed;
    if (m_timeOffset > 0) {
        return;
    } else {
        m_physicsObject->setVelocity(m_currentVelocity);
    }

    if (m_timeTilNextPlatform > 0) {
        m_timeTilNextPlatform -= elapsed;
        m_waitTime = 0.0f;
    } else {
        if (m_movingForward) {
            auto const hasReachedLastPosition = m_currentIndex >= m_positions.size() - 2;
            if (hasReachedLastPosition) {
                if (moveFromTo(
                        m_positions[m_currentIndex + 1], m_positions[m_currentIndex], elapsed)) {
                    m_movingForward = false;
                }
            } else {
                if (moveFromTo(m_positions[m_currentIndex + 1], m_positions[m_currentIndex + 2],
                        elapsed)) {
                    m_currentIndex++;
                }
            }
        } else {
            auto const hasReachedFirstPosition = m_currentIndex <= 0;
            if (hasReachedFirstPosition) {
                if (moveFromTo(
                        m_positions[m_currentIndex], m_positions[m_currentIndex + 1], elapsed)) {
                    m_movingForward = true;
                }
            } else {
                if (moveFromTo(
                        m_positions[m_currentIndex], m_positions[m_currentIndex - 1], elapsed)) {
                    m_currentIndex--;
                }
            }
        }
    }

    if (m_linkedKillbox) {
        m_linkedKillbox->setPosition(m_physicsObject->getPosition() + m_linkedKillboxOffset);
    }
}

void MovingPlatform::doDraw() const
{
    auto numberOfMiddlePartsY = static_cast<int>(m_platformSize.y) / 8;
    for (int j = 0; j != numberOfMiddlePartsY; ++j) {
        m_spriteL->setPosition(m_physicsObject->getPosition() + jt::Vector2f { 0.0f, j * 8.0f });
        m_spriteL->update(0.0f);
        m_spriteL->draw(renderTarget());

        auto numberOfMiddlePartsX = static_cast<int>(m_platformSize.x) / 8 - 2;

        for (int i = 0; i != numberOfMiddlePartsX; ++i) {
            m_spriteM->setPosition(
                m_physicsObject->getPosition() + jt::Vector2f { (i + 1) * 8.0f, j * 8.0f });
            m_spriteM->update(0.0f);
            m_spriteM->draw(renderTarget());
        }
        m_spriteR->setPosition(
            m_physicsObject->getPosition() + jt::Vector2f { m_platformSize.x - 8, j * 8.0f });
        m_spriteR->update(0.0f);
        m_spriteR->draw(renderTarget());
    }
}

void MovingPlatform::setLinkedKillbox(std::shared_ptr<Killbox> kb)
{
    m_linkedKillbox = kb;
    m_linkedKillboxOffset = kb->getPosition() - m_positions[0].first;
}
