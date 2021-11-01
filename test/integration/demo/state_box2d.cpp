#include "state_box2d.hpp"
#include "conversions.hpp"
#include "game_interface.hpp"
#include "input_manager.hpp"
#include "lerp.hpp"
#include "movement_object.hpp"
#include "random.hpp"
#include "state_select.hpp"
#include "tweens/tween_rotation.hpp"
#include "tweens/tween_scale.hpp"

void StateBox2d::doInternalCreate()
{
    CreateWalls();

    CreatePlayer();

    m_bar1 = std::make_shared<jt::Bar>(100.0f, 10.0f);
    m_bar1->setPosition(jt::Vector2 { 10, 10 });

    m_bar2 = std::make_shared<jt::Bar>(100.0f, 10.0f);
    m_bar2->setPosition(jt::Vector2 { 10, 25 });
    m_bar2->setMaxValue(2.0f);
}

void StateBox2d::doInternalUpdate(float const elapsed)
{
    int32 const velocityIterations = 6;
    int32 const positionIterations = 2;

    m_world->Step(elapsed, velocityIterations, positionIterations);

    updateObjects(elapsed);

    m_bar1->update(elapsed);
    m_bar2->update(elapsed);

    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->switchState(std::make_shared<StateSelect>());
    }

    float max_T = 5.5f;
    float current = getAge() / max_T;
    while (current > 1) {
        current = current - 1.0f;
    }
    if (current < 0) {
        current = 0;
    }
    float v = jt::Lerp::cosine(0.0f, 1.0f, current);
    m_bar1->setCurrentValue(v);
    if (current < 0.25f) {
        m_bar1->setFrontColor(jt::colors::Red);
    } else {
        m_bar1->setFrontColor(jt::colors::White);
    }

    m_bar2->setCurrentValue((1 - v));
    m_bar2->setBackColor(jt::colors::Blue);
}

void StateBox2d::doInternalDraw() const
{
    drawObjects();
    m_bar1->draw(getGame()->getRenderTarget());
    m_bar2->draw(getGame()->getRenderTarget());
}

void StateBox2d::CreateOneWall(jt::Vector2 const& pos)
{
    b2BodyDef groundBodyDef;
    groundBodyDef.fixedRotation = true;
    groundBodyDef.position = jt::Conversion::vec(pos);
    MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
    add(b2obj);

    auto const tweenstartDelay = jt::Random::getFloatGauss(0.3f, 0.05f);

    auto tw1 = jt::TweenRotation::create(
        b2obj->getAnimation(), jt::Random::getFloatGauss(0.75f, 0.1f), 0, 360);
    tw1->setStartDelay(tweenstartDelay);
    add(tw1);

    auto tw2 = jt::TweenScale::create(
        b2obj->getAnimation(), 0.75f, jt::Vector2 { 0.0f, 0.0f }, jt::Vector2 { 1.0f, 1.0f });
    tw2->setStartDelay(tweenstartDelay);
    add(tw2);
}

void StateBox2d::CreateWalls()
{
    b2BodyDef groundBodyDef;
    groundBodyDef.fixedRotation = true;
    for (int i = 0; i != 30; ++i) {
        auto const i_as_float = static_cast<float>(i);
        // ceiling
        CreateOneWall(jt::Vector2 { i_as_float * 16.0f, 0.0f });

        // floor layers
        CreateOneWall(jt::Vector2 { i_as_float * 16.0f, 320.0f });
        CreateOneWall(jt::Vector2 { i_as_float * 16.0f, 320.0f - 16.0f });
        CreateOneWall(jt::Vector2 { i_as_float * 16.0f, 320.0f - 32.0f });

        // walls

        CreateOneWall(jt::Vector2 { 0.0f, 16.0f * i_as_float });
        CreateOneWall(jt::Vector2 { 400.0f - 16.0f, 16.0f * i_as_float });
    }
}
void StateBox2d::CreatePlayer()
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(48, 32.0f);
    MovementObject::Sptr myBody = std::make_shared<MovementObject>(m_world, &bodyDef);

    add(myBody);
    {
        auto tw = jt::TweenRotation::create(myBody->getAnimation(), 2, 0, 360);
        tw->setRepeat(true);
        add(tw);
    }
}
