﻿#ifndef GAME_OBJECT_HPP_INCLUDEGUARD
#define GAME_OBJECT_HPP_INCLUDEGUARD

#include "Animation.hpp"
#include "GameInterface.hpp"
#include "GameState.hpp"
#include "MathHelper.hpp"
#include "Random.hpp"
#include "Shape.hpp"
#include <iostream>
#include <memory>
#include <random>

class Object : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<Object>;
    Object() { }

    ~Object() = default;

    void Flash() { m_animation->flash(0.1f); }
    void Shake() { m_animation->shake(0.5f, 2.0f, 0.05f); }

    std::shared_ptr<jt::Animation> getAnimation() { return m_animation; }

private:
    void doCreate() override
    {
        m_animation = std::make_shared<jt::Animation>();
        m_animation->add("assets/coin.png", "idle", jt::Vector2u { 16, 16 },
            jt::MathHelper::vectorBetween(0U, 11U), 0.15f);
        m_animation->play("idle");

        m_animation->setColor(jt::Random::getRandomColor());

        float x = jt::Random::getFloat(180, 220) - 8;
        float y = jt::Random::getFloat(135, 165) - 8;

        float vx = jt::Random::getFloatGauss(0, 50);
        float vy = jt::Random::getFloatGauss(0, 50);

        m_position = jt::Vector2 { x, y };
        m_velocity = jt::Vector2 { vx, vy };
        m_acceleration = jt::Vector2 { 0.0f, -50.0f / 2.0f };
    }
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

    std::shared_ptr<jt::Animation> m_animation;
    jt::Vector2 m_position;
    jt::Vector2 m_velocity;
    jt::Vector2 m_acceleration;
};

#endif
