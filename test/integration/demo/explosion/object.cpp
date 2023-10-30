#include "object.hpp"
#include <game_interface.hpp>
#include <math_helper.hpp>
#include <random/random.hpp>

void Object::Flash() { m_animation->flash(0.1f); }

void Object::Shake() { m_animation->shake(0.5f, 2.0f, 0.05f); }

std::shared_ptr<jt::Animation> Object::getAnimation() { return m_animation; }

void Object::doCreate()
{
    m_animation = std::make_shared<jt::Animation>();
    m_animation->add("assets/test/integration/demo/coin.png", "idle", jt::Vector2u { 16, 16 },
        jt::MathHelper::numbersBetween(0u, 11u), 0.15f, textureManager());
    m_animation->play("idle");

    m_animation->setColor(jt::Random::getRandomColor());

    float x = jt::Random::getFloat(180, 220) - 8;
    float y = jt::Random::getFloat(135, 165) - 8;

    float vx = jt::Random::getFloatGauss(0, 50);
    float vy = jt::Random::getFloatGauss(0, 50);

    m_position = jt::Vector2f { x, y };
    m_velocity = jt::Vector2f { vx, vy };
    m_acceleration = jt::Vector2f { 0.0f, -50.0f / 2.0f };
}

void Object::doUpdate(float const elapsed)
{
    m_velocity = m_velocity + elapsed * m_acceleration;
    m_position = m_position + elapsed * m_velocity;
    m_animation->setPosition(m_position);
    m_animation->update(elapsed);
    if (getAge() > 0.9)
        kill();
}

void Object::doDraw() const { m_animation->draw(renderTarget()); }
