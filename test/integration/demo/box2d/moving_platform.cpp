#include "moving_platform.hpp"
#include <math_helper.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

MovingPlatform::MovingPlatform(std::shared_ptr<jt::Box2DWorldInterface> world,
    jt::Vector2f const& size, std::vector<jt::Vector2f> const& positions, float velocity)
{
    m_platformSize = size;
    m_positions = positions;
    m_velocity = velocity;

    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_kinematicBody;
    m_physicsObject = std::make_shared<jt::Box2DObject>(world, &bodyDef);
}

void MovingPlatform::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(m_platformSize, textureManager());
    m_shape->setColor(jt::colors::Blue);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f;
    b2PolygonShape collider {};
    collider.SetAsBox(m_platformSize.x / 2.0f, m_platformSize.y / 2.0f,
        b2Vec2(m_platformSize.x / 2.0f, m_platformSize.y / 2.0f), 0);
    fixtureDef.shape = &collider;
    m_physicsObject->getB2Body()->CreateFixture(&fixtureDef);

    auto const p1 = m_positions[m_currentIndex];

    auto const p2 = m_positions[m_currentIndex + 1];

    auto const totalDiff = p2 - p1;
    auto diff = totalDiff;
    jt::MathHelper::normalizeMe(diff);
    m_currentVelocity = diff * m_velocity;

    m_timeTilNextPlatform = jt::MathHelper::length(totalDiff) / m_velocity;
    m_physicsObject->setPosition(p1);
    m_physicsObject->setVelocity(m_currentVelocity);
}

void MovingPlatform::doUpdate(float const elapsed)
{
    if (m_timeTilNextPlatform > 0) {
        m_timeTilNextPlatform -= elapsed;
    } else {

        if (m_movingForward) {
            if (m_currentIndex >= m_positions.size() - 2) {

                m_physicsObject->setVelocity(jt::Vector2f { 0.0f, 0.0f });
                m_movingForward = false;

                auto const p1 = m_positions[m_currentIndex + 1];
                auto const p2 = m_positions[m_currentIndex];

                auto const totalDiff = p2 - p1;
                auto diff = totalDiff;
                jt::MathHelper::normalizeMe(diff);
                m_currentVelocity = diff * m_velocity;

                m_timeTilNextPlatform = jt::MathHelper::length(totalDiff) / m_velocity;
                m_physicsObject->setPosition(p1);

                m_physicsObject->setVelocity(m_currentVelocity);

            } else {
                m_currentIndex++;
                auto const p1 = m_positions[m_currentIndex];
                auto const p2 = m_positions[m_currentIndex + 1];

                auto const totalDiff = p2 - p1;
                auto diff = totalDiff;
                jt::MathHelper::normalizeMe(diff);
                m_currentVelocity = diff * m_velocity;

                m_timeTilNextPlatform = jt::MathHelper::length(totalDiff) / m_velocity;
                m_physicsObject->setPosition(p1);

                m_physicsObject->setVelocity(m_currentVelocity);
            }
        } else {
            if (m_currentIndex <= 0) {
                m_physicsObject->setVelocity(jt::Vector2f { 0.0f, 0.0f });
                m_movingForward = true;

                auto const p1 = m_positions[m_currentIndex];
                auto const p2 = m_positions[m_currentIndex + 1];

                auto const totalDiff = p2 - p1;
                auto diff = totalDiff;
                jt::MathHelper::normalizeMe(diff);
                m_currentVelocity = diff * m_velocity;

                m_timeTilNextPlatform = jt::MathHelper::length(totalDiff) / m_velocity;
                m_physicsObject->setPosition(p1);

                m_physicsObject->setVelocity(m_currentVelocity);

            } else {

                auto const p1 = m_positions[m_currentIndex];
                auto const p2 = m_positions[m_currentIndex - 1];
                m_currentIndex--;
                auto const totalDiff = p2 - p1;
                auto diff = totalDiff;
                jt::MathHelper::normalizeMe(diff);
                m_currentVelocity = diff * m_velocity;

                m_timeTilNextPlatform = jt::MathHelper::length(totalDiff) / m_velocity;
                m_physicsObject->setPosition(p1);

                m_physicsObject->setVelocity(m_currentVelocity);
            }
        }
    }
    m_shape->setPosition(m_physicsObject->getPosition());
    m_shape->update(elapsed);
}

void MovingPlatform::doDraw() const { m_shape->draw(renderTarget()); }
