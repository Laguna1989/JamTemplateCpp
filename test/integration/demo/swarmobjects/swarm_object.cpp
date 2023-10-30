#include "swarm_object.hpp"

void SwarmObject::doCreate()
{
    m_animation = std::make_shared<jt::Animation>();

    m_swarmWeight = jt::Random::getFloat(0.5f, 1.5f);

    float maxX = 400 - 12;
    float maxY = 300 - 12;

    m_animation->add("assets/test/integration/demo/coin.png", "idle", jt::Vector2u { 16, 16 },
        jt::MathHelper::numbersBetween(0u, 11u), jt::Random::getFloat(0.13f, 0.17f),
        textureManager());
    m_animation->play("idle", jt::Random::getInt(0, 6));

    setPosition(
        jt::Vector2f { jt::Random::getFloat(0, maxX / 2), jt::Random::getFloat(0, maxY / 2) });
}

void SwarmObject::setPosition(jt::Vector2f const& p) { m_position = p; }
jt::Vector2f SwarmObject::getPosition() const { return m_position; }
void SwarmObject::setVelocity(jt::Vector2f const& p) { m_velocity = p; }
jt::Vector2f SwarmObject::getVelocity() const { return m_velocity; }
void SwarmObject::setAcceleration(jt::Vector2f const& p) { m_acceleration = p; }
void SwarmObject::doUpdate(float const elapsed)
{
    m_velocity = m_velocity + m_acceleration * elapsed;
    m_position = m_position + elapsed * m_velocity;
    m_animation->setPosition(getPosition());
    m_animation->update(elapsed);
    m_acceleration = jt::Vector2f { 0.0f, 0.0f };
}
void SwarmObject::doDraw() const { m_animation->draw(renderTarget()); }
