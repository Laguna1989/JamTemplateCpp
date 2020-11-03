#ifndef STRESSTEST_STATE_2_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_2_HPP_INCLUDEGUARD

#include "Collision.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "ObjectGroup.hpp"
#include "SmartShape.hpp"
#include "SmartSprite.hpp"
#include "SwarmObject.hpp"
#include "Timer.hpp"
#include "TweenAlpha.hpp"
#include <iostream>
#include <vector>

class State2 : public JamTemplate::GameState {
public:
    State2() = default;

private:
    JamTemplate::SmartShape::Sptr m_overlay;
    JamTemplate::SmartShape::Sptr m_sky;

    JamTemplate::ObjectGroup<SwarmObject>::Sptr m_SwarmObjects;

    void doInternalUpdate(float const /*elapsed*/) override;

    void doCreate() override
    {

        m_sky = std::make_shared<JamTemplate::SmartShape>();
        m_sky->makeRect(sf::Vector2f(200, 150));
        m_sky->setColor(sf::Color { 178, 255, 255 });

        using JamTemplate::SmartShape;
        using JamTemplate::TweenAlpha;

        m_overlay = std::make_shared<SmartShape>();
        m_overlay->makeRect(sf::Vector2f { 200, 200 });
        m_overlay->setColor(sf::Color { 0, 0, 0 });
        m_overlay->update(0.0f);
        auto tw
            = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, sf::Uint8 { 255 }, sf::Uint8 { 0 });
        tw->addCompleteCallback([this]() { std::cout << "overlay fade in finished" << std::endl; });
        add(tw);

        m_SwarmObjects = std::make_shared<JamTemplate::ObjectGroup<SwarmObject>>();
        add(m_SwarmObjects);
        for (int i = 0; i != 50; ++i) {
            SwarmObject::Sptr sptr = std::make_shared<SwarmObject>();
            add(sptr);
            m_SwarmObjects->push_back(sptr);
        }

        m_sky->update(0.0f);
    }

    void drawSky() const { m_sky->draw(getGame()->getRenderTarget()); }

    void doDraw() const override
    {
        drawSky();
        drawObjects();
        m_overlay->draw(getGame()->getRenderTarget());
    }
};

#endif
