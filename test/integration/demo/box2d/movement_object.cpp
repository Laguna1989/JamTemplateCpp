#include "movement_object.hpp"
#include <conversions.hpp>
#include <game_interface.hpp>
#include <math_helper.hpp>

MovementObject::MovementObject(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : Box2DObject { world, def }
{
    m_type = def->type;
}

void MovementObject::doCreate()
{
    m_animation = std::make_shared<jt::Animation>();
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 5.0f;
    if (m_type == b2BodyType::b2_dynamicBody) {
        m_animation->add("assets/coin.png", "idle", jt::Vector2u { 16, 16 },
            jt::MathHelper::numbersBetween(0U, 11U), 0.13f, textureManager());
        m_animation->play("idle");
        m_animation->setOffset(jt::Vector2f { 8, 8 });
        m_animation->setOrigin(jt::Vector2f { 8, 8 });

        b2CircleShape circleCollider {};
        circleCollider.m_radius = 8.0f;
        fixtureDef.shape = &circleCollider;
        getB2Body()->CreateFixture(&fixtureDef);

    } else {
        m_animation->add(
            "assets/wall.png", "idle", jt::Vector2u { 16, 16 }, { 0 }, 100.0f, textureManager());
        m_animation->play("idle");
        m_animation->setOffset(jt::Vector2f { 8, 8 });
        m_animation->setOrigin(jt::Vector2f { 8, 8 });

        b2PolygonShape boxCollider {};
        boxCollider.SetAsBox(8, 8);
        fixtureDef.shape = &boxCollider;
        getB2Body()->CreateFixture(&fixtureDef);
    }
}

std::shared_ptr<jt::Animation> MovementObject::getAnimation() { return m_animation; }

void MovementObject::doUpdate(float const elapsed)
{
    using namespace jt::Conversion;
    m_animation->setPosition(vec(getB2Body()->GetPosition()));

    m_animation->update(elapsed);
    if (getB2Body()->GetType() == b2BodyType::b2_dynamicBody) {
        if (getGame()->input().keyboard()->pressed(jt::KeyCode::D)) {
            getB2Body()->ApplyForceToCenter(b2Vec2 { 60000, 0 }, true);
        }

        if (getGame()->input().keyboard()->pressed(jt::KeyCode::A)) {
            getB2Body()->ApplyForceToCenter(b2Vec2 { -60000, 0 }, true);
        }
    }

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::B)) {
        m_animation->flash(0.5f, jt::colors::Red);
    }
}

void MovementObject::doDraw() const { m_animation->draw(renderTarget()); }
