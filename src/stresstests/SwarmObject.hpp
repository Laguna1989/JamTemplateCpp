#ifndef STRESSTEST_SWARMOBJECT_HPP_INCLUDEGUARD
#define STRESSTEST_SWARMOBJECT_HPP_INCLUDEGUARD

#include "Animation.hpp"
#include "GameInterface.hpp"
#include "GameState.hpp"
#include "MathHelper.hpp"
#include "ObjectGroup.hpp"
#include "Random.hpp"
#include "Shape.hpp"
#include <iostream>
#include <memory>
#include <random>

class SwarmObject : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<SwarmObject>;
    SwarmObject()
    {
        m_animation = std::make_shared<jt::Animation>();

        m_swarmWeight = jt::Random::getFloat(0.5f, 1.5f);

        float maxX = 200 - 12;
        float maxY = 150 - 12;

        m_animation->add("assets/coin.png", "idle", jt::Vector2u { 16, 16 },
            jt::MathHelper::vectorBetween(0U, 11U), jt::Random::getFloat(0.13f, 0.17f));
        m_animation->play("idle", jt::Random::getInt(0, 6));
        m_animation->setScale(jt::Vector2 { 0.5f, 0.5f });

        setPosition(
            jt::Vector2(jt::Random::getFloat(0, maxX / 2), jt::Random::getFloat(0, maxY / 2)));
        /*float mv = 50;*/
        // setBoundsVelocity(jt::Rect { -mv, -mv, 2 * mv, 2 * mv });
        // setBoundsPosition(jt::Rect { 0, 0, maxX, maxY });
    }

    ~SwarmObject() = default;

    std::shared_ptr<jt::Animation> getAnimation() { return m_animation; }

    float getSwarmWeight() const { return m_swarmWeight; }

    void setPosition(jt::Vector2 const& p) { m_position = p; }
    jt::Vector2 getPosition() const { return m_position; }

    void setVelocity(jt::Vector2 const& p) { m_velocity = p; }
    jt::Vector2 getVelocity() const { return m_velocity; }

private:
    std::shared_ptr<jt::Animation> m_animation;
    float m_swarmWeight = 0.0f;
    jt::Vector2 m_position { 0.0f, 0.0f };
    jt::Vector2 m_velocity { 0.0f, 0.0f };
    jt::Vector2 m_acceleration { 0.0f, 0.0f };

    void doUpdate(float const elapsed) override
    {
        // updateTransform(elapsed);
        m_position = m_position + elapsed * m_velocity;
        m_animation->setPosition(getPosition());
        m_animation->update(elapsed);
    }

    void doDraw() const override { m_animation->draw(getGame()->getRenderTarget()); }
};

#endif
