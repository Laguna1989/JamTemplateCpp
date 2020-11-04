#ifndef STRESSTEST_SWARMOBJECT_HPP_INCLUDEGUARD
#define STRESSTEST_SWARMOBJECT_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "MathHelper.hpp"
#include "ObjectGroup.hpp"
#include "Random.hpp"
#include "SmartAnimation.hpp"
#include "SmartShape.hpp"
#include "Transform.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <random>

class SwarmObject : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
    using Sptr = std::shared_ptr<SwarmObject>;
    SwarmObject()
    {
        m_animation = std::make_shared<JamTemplate::SmartAnimation>();

        m_swarmWeight = JamTemplate::Random::getFloat(0.5f, 1.5f);

        float maxX = 200 - 12;
        float maxY = 150 - 12;

        m_animation->add("assets/coin.png", "idle", sf::Vector2u { 16, 16 },
            JamTemplate::MathHelper::vectorBetween(0U, 11U),
            JamTemplate::Random::getFloat(0.13f, 0.17f));
        m_animation->play("idle", JamTemplate::Random::getInt(0, 6));
        m_animation->setScale(sf::Vector2f { 0.5f, 0.5f });

        setPosition(sf::Vector2f(JamTemplate::Random::getFloat(0, maxX / 2),
            JamTemplate::Random::getFloat(0, maxY / 2)));
        float mv = 50;
        setBoundsVelocity(sf::FloatRect { -mv, -mv, 2 * mv, 2 * mv });
        setBoundsPosition(sf::FloatRect { 0, 0, maxX, maxY });
    }

    ~SwarmObject() = default;

    std::shared_ptr<JamTemplate::SmartAnimation> getAnimation() { return m_animation; }

    float getSwarmWeight() const { return m_swarmWeight; }

private:
    std::shared_ptr<JamTemplate::SmartAnimation> m_animation;
    float m_swarmWeight = 0.0f;

    void doUpdate(float const elapsed) override
    {
        updateTransform(elapsed);
        m_animation->setPosition(getPosition());
        m_animation->update(elapsed);
    }

    void doDraw() const override { m_animation->draw(getGame()->getRenderTarget()); }
};

#endif
