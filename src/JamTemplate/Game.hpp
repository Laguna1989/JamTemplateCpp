#ifndef JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "Random.hpp"
#include "SmartObject.hpp"

namespace JamTemplate {

class Game final : public GameObject, public std::enable_shared_from_this<Game> {
public:
    using Sptr = std::shared_ptr<Game>;
    Game()
        : m_state { nullptr }
        , m_backgroundColor { sf::Color::Black }
    {
    }

    void setUp(unsigned int w, unsigned int h, float zoom, std::string title)
    {
        m_renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(w, h), title, sf::Style::Close);
        m_renderWindow->setFramerateLimit(60);

        m_renderTarget = std::make_shared<sf::RenderTexture>();
        m_renderTarget->create(static_cast<unsigned int>(w / zoom), static_cast<unsigned int>(h / zoom), false);
        m_renderTarget->setSmooth(false);

        m_view = std::make_shared<sf::View>(sf::FloatRect(0, 0, (float)static_cast<unsigned int>(w / zoom), (float)static_cast<unsigned int>(h / zoom)));
        m_view->setViewport(sf::FloatRect(0, 0, 1, 1));

        m_zoom = zoom;
    }

    float getZoom() const
    {
        return m_zoom;
    }

    void switchState(GameState::Sptr newState)
    {
        //std::cout << "switchstate\n";
        if (newState == nullptr) {
            std::cerr << "cannot switch to nullptr state!" << std::endl;
            return;
        }
        //m_state = newState;
        m_nextState = newState;
    }

    void setRenderTarget(std::shared_ptr<sf::RenderTexture> rt)
    {
        m_renderTarget = rt;
    }
    std::shared_ptr<sf::RenderTexture> getRenderTarget()
    {
        return m_renderTarget;
    }

    void setRenderWindow(std::shared_ptr<sf::RenderWindow> w)
    {
        m_renderWindow = w;
    }
    std::shared_ptr<sf::RenderWindow> getRenderWindow()
    {
        return m_renderWindow;
    }

    void setView(std::shared_ptr<sf::View> view)
    {
        m_view = view;
        if (m_renderTarget != nullptr)
            m_renderTarget->setView(*m_view);
    }
    std::shared_ptr<sf::View> getView()
    {
        return m_view;
    }

    sf::Vector2f getCamOffset()
    {
        return sf::Vector2f { getView()->getCenter().x - getView()->getSize().x / 2, getView()->getCenter().y - getView()->getSize().y / 2 };
    }

    void shake(float t, float strength, float shakeInterval = 0.005f)
    {
        m_shakeTimer = t;
        m_shakeStrength = strength;
        m_shakeInterval = m_shakeIntervalMax = shakeInterval;
    }

private:
    GameState::Sptr m_state { nullptr };
    GameState::Sptr m_nextState { nullptr };
    std::shared_ptr<sf::RenderTexture> m_renderTarget { nullptr };
    std::shared_ptr<sf::View> m_view { nullptr };
    std::shared_ptr<sf::RenderWindow> m_renderWindow { nullptr };

    float m_zoom { 1.0f };

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    sf::Vector2f m_shakeOffset { 0, 0 };

    sf::Color m_backgroundColor { sf::Color::Black };

    std::weak_ptr<Game> getPtr()
    {
        return shared_from_this();
    }

    virtual void doUpdate(float const elapsed) override
    {
        //std::cout << "game::update\n";
        if (m_nextState != nullptr) {
            doSwitchState();
            return;
        }
        if (m_state == nullptr)
            return;

        SmartObject::setCamOffset(getCamOffset());
        sf::Vector2f mpf = getRenderWindow()->mapPixelToCoords(sf::Mouse::getPosition(*getRenderWindow()), *getView());
        sf::Vector2f mpfs = getRenderWindow()->mapPixelToCoords(sf::Mouse::getPosition(*getRenderWindow())) / m_zoom;
        InputManager::update(mpf.x, mpf.y, mpfs.x, mpfs.y);

        updateShake(elapsed);
        m_state->update(elapsed);
    };

    virtual void doDraw() const override
    {
        // clear the old image
        m_renderTarget->clear(m_backgroundColor);
        //m_renderWindow->clear(m_backgroundColor);

        if (m_state == nullptr)
            return;
        m_state->draw();

        // convert renderTexture to sprite and draw that.
        const sf::Texture& texture = m_renderTarget->getTexture();
        sf::Sprite spr(texture);
        //Note: RenderTexture has a bug and is displayed upside down.
        //This is corrected by the following two lines
        spr.setScale(sf::Vector2f(m_zoom, -m_zoom));
        spr.setPosition(0.0f, static_cast<float>(m_renderWindow->getSize().y));

        // draw the sprite
        m_renderWindow->draw(spr);

        // blit it to the screen
        m_renderWindow->display();
    };

    void updateShake(float elapsed)
    {
        if (m_shakeOffset.x != 0 || m_shakeOffset.y != 0) {
            getView()->move(-m_shakeOffset.x, -m_shakeOffset.y);
        }

        if (m_shakeTimer > 0) {

            m_shakeTimer -= elapsed;
            m_shakeInterval -= elapsed;
            if (m_shakeInterval < 0) {
                m_shakeInterval = m_shakeIntervalMax;
                m_shakeOffset.x = JamTemplate::Random::getFloat(-m_shakeStrength, m_shakeStrength);
                m_shakeOffset.y = JamTemplate::Random::getFloat(-m_shakeStrength, m_shakeStrength);
            }
        } else {
            m_shakeOffset.x = m_shakeOffset.y = 0;
        }

        auto v = getView();
        v->move(m_shakeOffset.x, m_shakeOffset.y);
        setView(v);
    }

    void resetShake()
    {
        if (m_shakeOffset.x != 0 || m_shakeOffset.y != 0) {
            getView()->move(-m_shakeOffset.x, -m_shakeOffset.y);
        }
        m_shakeOffset.x = m_shakeOffset.y = 0;
        m_shakeTimer = -1;
        m_shakeStrength = 0;
    }

    void doSwitchState()
    {
        m_state = m_nextState;
        m_nextState = nullptr;

        m_state->setGameInstance(getPtr());
        m_state->create();

        resetShake();
    }
};

}
#endif
