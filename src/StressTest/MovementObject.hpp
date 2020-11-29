#ifndef STRESSTEST_MOVEMENTOBJECT_HPP_INCLUDEGUARD
#define STRESSTEST_MOVEMENTOBJECT_HPP_INCLUDEGUARD

#include "Box2DObject.hpp"
#include "Conversions.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "MathHelper.hpp"
#include "ObjectGroup.hpp"
#include "Random.hpp"
#include "SmartAnimation.hpp"
#include "SmartShape.hpp"
#include <iostream>
#include <memory>
#include <random>

class MovementObject : public jt::Box2DObject {
public:
    using Sptr = std::shared_ptr<MovementObject>;
    MovementObject(std::shared_ptr<b2World> world, const b2BodyDef* def)
        : Box2DObject { world, def }
    {
        m_animation = std::make_shared<jt::SmartAnimation>();

        m_animation->add("assets/coin.png", "idle", jt::vector2u { 16, 16 },
            jt::MathHelper::vectorBetween(0U, 11U), jt::Random::getFloat(0.13f, 0.17f));
        m_animation->play("idle", jt::Random::getInt(0, 6));
        m_animation->setOffset(jt::vector2 { -8, -8 });
        m_animation->setOrigin(jt::vector2 { 8, 8 });

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(8, 8);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.9f;

        getB2Body()->CreateFixture(&fixtureDef);
    }

    ~MovementObject() = default;

    std::shared_ptr<jt::SmartAnimation> getAnimation() { return m_animation; }

private:
    std::shared_ptr<jt::SmartAnimation> m_animation;

    void doUpdate(float const elapsed) override
    {
        using namespace jt::Conversion;
        m_animation->setPosition(vec(getB2Body()->GetPosition()));

        m_animation->update(elapsed);
        if (getB2Body()->GetType() == b2BodyType::b2_dynamicBody) {
            if (jt::InputManager::pressed(jt::KeyCode::D)) {
                getB2Body()->ApplyForceToCenter(b2Vec2 { 1000, 0 }, true);
            }

            if (jt::InputManager::pressed(jt::KeyCode::A)) {
                getB2Body()->ApplyForceToCenter(b2Vec2 { -1000, 0 }, true);
            }
        }

        if (jt::InputManager::pressed(jt::KeyCode::B)) {
            m_animation->flash(0.5f, jt::colors::Red);
        }
    }

    void doDraw() const override { m_animation->draw(getGame()->getRenderTarget()); }
};

#endif
