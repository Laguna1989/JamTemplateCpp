#ifndef STRESSTEST_SWARMOBJECT_HPP_INCLUDEGUARD
#define STRESSTEST_SWARMOBJECT_HPP_INCLUDEGUARD

#include "animation.hpp"
#include "game_interface.hpp"
#include "game_state.hpp"
#include "math_helper.hpp"
#include "random/random.hpp"
#include <memory>

class SwarmObject : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<SwarmObject>;
    SwarmObject() { }

    void doCreate() override
    {
        m_animation = std::make_shared<jt::Animation>();

        m_swarmWeight = jt::Random::getFloat(0.5f, 1.5f);

        float maxX = 400 - 12;
        float maxY = 300 - 12;

        m_animation->add("assets/coin.png", "idle", jt::Vector2u { 16, 16 },
            jt::MathHelper::numbersBetween(0U, 11U), jt::Random::getFloat(0.13f, 0.17f),
            getGame()->gfx().textureManager());
        m_animation->play("idle", jt::Random::getInt(0, 6));

        setPosition(
            jt::Vector2f { jt::Random::getFloat(0, maxX / 2), jt::Random::getFloat(0, maxY / 2) });
    }

    ~SwarmObject() = default;

    std::shared_ptr<jt::Animation> getAnimation() { return m_animation; }

    float getSwarmWeight() const { return m_swarmWeight; }

    void setPosition(jt::Vector2f const& p) { m_position = p; }
    jt::Vector2f getPosition() const { return m_position; }

    void setVelocity(jt::Vector2f const& p) { m_velocity = p; }
    jt::Vector2f getVelocity() const { return m_velocity; }

    void setAcceleration(jt::Vector2f const& p) { m_acceleration = p; }
    jt::Vector2f getAcceleration() const { return m_acceleration; }

private:
    std::shared_ptr<jt::Animation> m_animation;
    float m_swarmWeight = 0.0f;
    jt::Vector2f m_position { 0.0f, 0.0f };
    jt::Vector2f m_velocity { 0.0f, 0.0f };
    jt::Vector2f m_acceleration { 0.0f, 0.0f };

    void doUpdate(float const elapsed) override
    {
        m_velocity = m_velocity + m_acceleration * elapsed;
        m_position = m_position + elapsed * m_velocity;
        m_animation->setPosition(getPosition());
        m_animation->update(elapsed);
        m_acceleration = jt::Vector2f { 0.0f, 0.0f };
    }

    void doDraw() const override { m_animation->draw(getGame()->gfx().target()); }
};

#endif
