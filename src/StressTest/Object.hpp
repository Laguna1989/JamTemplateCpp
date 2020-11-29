#ifndef GAME_OBJECT_HPP_INCLUDEGUARD
#define GAME_OBJECT_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "MathHelper.hpp"
#include "Random.hpp"
#include "SmartAnimation.hpp"
#include "SmartShape.hpp"
#include <iostream>
#include <memory>
#include <random>

class Object : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<Object>;
    Object()
    {
        m_animation = std::make_shared<jt::SmartAnimation>();
        // m_shape->makeRect(jt::vector2(10, 10));
        m_animation->add("assets/coin.png", "idle", jt::vector2u { 16, 16 },
            jt::MathHelper::vectorBetween(0U, 11U), 0.15f);
        m_animation->play("idle");

        m_animation->setColor(jt::Random::getRandomColor());

        float x = jt::Random::getFloat(80, 120) - 8;
        float y = jt::Random::getFloat(55, 95) - 8;

        float vx = jt::Random::getFloatGauss(0, 50);
        float vy = jt::Random::getFloatGauss(0, 50);

        m_position = jt::vector2 { x, y };
        m_velocity = jt::vector2 { vx, vy };
        m_acceleration = jt::vector2 { 0.0f, -50.0f / 2.0f };
    }

    ~Object() = default;

    void Flash() { m_animation->flash(0.1f); }
    void Shake() { m_animation->shake(0.5f, 2.0f, 0.05f); }

    std::shared_ptr<jt::SmartAnimation> getAnimation() { return m_animation; }

private:
    void doUpdate(float const elapsed) override
    {
        m_velocity = m_velocity + elapsed * m_acceleration;
        m_position = m_position + elapsed * m_velocity;
        m_animation->setPosition(m_position);
        m_animation->update(elapsed);
        if (getAge() > 0.9)
            kill();
    }

    void doDraw() const override { m_animation->draw(getGame()->getRenderTarget()); }

    std::shared_ptr<jt::SmartAnimation> m_animation;
    jt::vector2 m_position;
    jt::vector2 m_velocity;
    jt::vector2 m_acceleration;
};

#endif
