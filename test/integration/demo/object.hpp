#ifndef GAME_OBJECT_HPP_INCLUDEGUARD
#define GAME_OBJECT_HPP_INCLUDEGUARD

#include "animation.hpp"
#include "game_interface.hpp"
#include "game_state.hpp"
#include "math_helper.hpp"
#include "random/random.hpp"
#include "shape.hpp"
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
            jt::MathHelper::numbersBetween(0U, 11U), 0.15f, getGame()->gfx().textureManager());
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
    void doUpdate(float const elapsed) override
    {
        m_velocity = m_velocity + elapsed * m_acceleration;
        m_position = m_position + elapsed * m_velocity;
        m_animation->setPosition(m_position);
        m_animation->update(elapsed);
        if (getAge() > 0.9)
            kill();
    }

    void doDraw() const override { m_animation->draw(getGame()->gfx().target()); }

    std::shared_ptr<jt::Animation> m_animation;
    jt::Vector2f m_position;
    jt::Vector2f m_velocity;
    jt::Vector2f m_acceleration;
};

#endif
