#ifndef STRESSTEST_SWARMOBJECT_HPP_INCLUDEGUARD
#define STRESSTEST_SWARMOBJECT_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "MathHelper.hpp"
#include "ObjectGroup.hpp"
#include "Random.hpp"
#include "SmartAnimation.hpp"
#include "SmartShape.hpp"
#include <iostream>
#include <memory>
#include <random>

class SwarmObject : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<SwarmObject>;
    SwarmObject()
    {
        m_animation = std::make_shared<jt::SmartAnimation>();

        m_swarmWeight = jt::Random::getFloat(0.5f, 1.5f);

        float maxX = 200 - 12;
        float maxY = 150 - 12;

        m_animation->add("assets/coin.png", "idle", jt::vector2u { 16, 16 },
            jt::MathHelper::vectorBetween(0U, 11U), jt::Random::getFloat(0.13f, 0.17f));
        m_animation->play("idle", jt::Random::getInt(0, 6));
        m_animation->setScale(jt::vector2 { 0.5f, 0.5f });

        /*setPosition(jt::vector2(jt::Random::getFloat(0, maxX / 2),
            jt::Random::getFloat(0, maxY / 2)));
        float mv = 50;
        setBoundsVelocity(jt::rect { -mv, -mv, 2 * mv, 2 * mv });
        setBoundsPosition(jt::rect { 0, 0, maxX, maxY });*/
    }

    ~SwarmObject() = default;

    std::shared_ptr<jt::SmartAnimation> getAnimation() { return m_animation; }

    float getSwarmWeight() const { return m_swarmWeight; }

private:
    std::shared_ptr<jt::SmartAnimation> m_animation;
    float m_swarmWeight = 0.0f;

    void doUpdate(float const elapsed) override
    {
        // updateTransform(elapsed);
        // m_animation->setPosition(getPosition());
        m_animation->update(elapsed);
    }

    void doDraw() const override { m_animation->draw(getGame()->getRenderTarget()); }
};

#endif
