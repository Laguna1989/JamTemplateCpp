#ifndef STRESSTEST_MOVEMENTOBJECT_HPP_INCLUDEGUARD
#define STRESSTEST_MOVEMENTOBJECT_HPP_INCLUDEGUARD

#include "Animation.hpp"
#include "Box2DObject.hpp"
#include "Conversions.hpp"
#include "GameInterface.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "MathHelper.hpp"
#include "ObjectGroup.hpp"
#include "Random.hpp"
#include "Shape.hpp"
#include <iostream>
#include <memory>
#include <random>

class MovementObject : public jt::Box2DObject {
public:
    using Sptr = std::shared_ptr<MovementObject>;
    MovementObject(std::shared_ptr<b2World> world, const b2BodyDef* def)
        : Box2DObject { world, def }
    {
        m_animation = std::make_shared<jt::Animation>();
        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 5.0f;

        if (def->type == b2BodyType::b2_dynamicBody) {
            m_animation->add("assets/coin.png", "idle", jt::Vector2u { 16, 16 },
                jt::MathHelper::vectorBetween(0U, 11U), 0.13f);
            m_animation->play("idle");
            m_animation->setOffset(jt::Vector2 { 8, 8 });
            m_animation->setOrigin(jt::Vector2 { 8, 8 });

            b2CircleShape circleCollider {};
            circleCollider.m_radius = 8.0f;
            fixtureDef.shape = &circleCollider;
            getB2Body()->CreateFixture(&fixtureDef);

        } else {
            m_animation->add("assets/wall.png", "idle", jt::Vector2u { 16, 16 }, { 0 }, 100.0f);
            m_animation->play("idle");
            m_animation->setOffset(jt::Vector2 { 8, 8 });
            m_animation->setOrigin(jt::Vector2 { 8, 8 });

            b2PolygonShape boxCollider {};
            boxCollider.SetAsBox(8, 8);
            fixtureDef.shape = &boxCollider;
            getB2Body()->CreateFixture(&fixtureDef);
        }
    }

    ~MovementObject() = default;

    std::shared_ptr<jt::Animation> getAnimation() { return m_animation; }

private:
    std::shared_ptr<jt::Animation> m_animation;

    void doUpdate(float const elapsed) override
    {
        using namespace jt::Conversion;
        m_animation->setPosition(vec(getB2Body()->GetPosition()));

        m_animation->update(elapsed);
        if (getB2Body()->GetType() == b2BodyType::b2_dynamicBody) {
            if (getGame()->input()->keyboard()->pressed(jt::KeyCode::D)) {
                getB2Body()->ApplyForceToCenter(b2Vec2 { 60000, 0 }, true);
            }

            if (getGame()->input()->keyboard()->pressed(jt::KeyCode::A)) {
                getB2Body()->ApplyForceToCenter(b2Vec2 { -60000, 0 }, true);
            }
        }

        if (getGame()->input()->keyboard()->pressed(jt::KeyCode::B)) {
            m_animation->flash(0.5f, jt::colors::Red);
        }
    }

    void doDraw() const override { m_animation->draw(getGame()->getRenderTarget()); }
};

#endif
