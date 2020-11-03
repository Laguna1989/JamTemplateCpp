#ifndef STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "MovementObject.hpp"
#include "PlayBar.hpp"
#include "SmartShape.hpp"
#include "TweenRotation.hpp"
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

class StateBox2d : public JamTemplate::GameState {
public:
    StateBox2d()
        : m_world { std::make_shared<b2World>(b2Vec2 { 0, 0.02f }) }
    {
    }

private:
    std::shared_ptr<b2World> m_world { nullptr };
    JamTemplate::PlayBar::Sptr m_bar1;
    JamTemplate::PlayBar::Sptr m_bar2;

    void doCreate() override
    {
        b2BodyDef groundBodyDef;
        groundBodyDef.fixedRotation = true;
        for (int i = 0; i != 20; ++i)
            for (int j = 0; j != 20; ++j) {
                groundBodyDef.position.Set(32.0f + i * 16, 100.0f - 16 + j * 16);
                MovementObject::Sptr b2obj
                    = std::make_shared<MovementObject>(m_world, &groundBodyDef);
                add(b2obj);

                auto tw = JamTemplate::TweenRotation<JamTemplate::Animation>::create(
                    b2obj->getAnimation(), 2, 0, 360);
                add(tw);
            }
        {
            groundBodyDef.position.Set(48, 100);
            MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
            add(b2obj);
        }
        {
            groundBodyDef.position.Set(64, 100);
            MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
            add(b2obj);
        }
        {
            groundBodyDef.position.Set(80, 100);
            MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
            add(b2obj);
        }
        {
            groundBodyDef.position.Set(96, 100);
            MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
            add(b2obj);
        }
        {
            groundBodyDef.position.Set(112, 100 - 16);
            MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
            add(b2obj);
        }

        b2BodyDef bodyDef;
        bodyDef.fixedRotation = true;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(48, 0.0f);
        MovementObject::Sptr myBody = std::make_shared<MovementObject>(m_world, &bodyDef);

        add(myBody);
        {
            auto tw = JamTemplate::TweenRotation<JamTemplate::Animation>::create(
                myBody->getAnimation(), 2, 0, 360);
            tw->setRepeat(true);
            add(tw);
        }

        m_bar1 = std::make_shared<JamTemplate::PlayBar>(100.0f, 10.0f);
        m_bar1->setPosition(sf::Vector2f { 10, 10 });
        add(m_bar1);

        m_bar2 = std::make_shared<JamTemplate::PlayBar>(100.0f, 10.0f);
        m_bar2->setPosition(sf::Vector2f { 10, 25 });
        m_bar2->setMaxValue(2.0f);
        add(m_bar2);
    }

    void doInternalUpdate(float const /*elapsed*/) override;
};

#endif
