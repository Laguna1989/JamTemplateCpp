#ifndef STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_TILESOM_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "SmartObject.hpp"
#include "SmartTilemap.hpp"

class StateTileson : public JamTemplate::GameState {
public:
    StateTileson() = default;

private:
    JamTemplate::SmartTilemap::Sptr m_tilemap;

    void doCreate() override
    {
        m_tilemap = std::make_shared<JamTemplate::SmartTilemap>(
            std::filesystem::path("assets/tileson_test.json"));
        m_tilemap->setScreenSizeHint(sf::Vector2f(400, 300), getGame());
    }

    void doDraw() const override { m_tilemap->draw(getGame()->getRenderTarget()); }
    void doUpdate(float const elapsed)
    {
        auto const scrollspeed = 50.0f;
        m_tilemap->update(elapsed);
        if (JamTemplate::InputManager::pressed(sf::Keyboard::D)) {
            getGame()->moveCam(sf::Vector2f { scrollspeed * elapsed, 0.0f });
        } else if (JamTemplate::InputManager::pressed(sf::Keyboard::A)) {
            getGame()->moveCam(sf::Vector2f { -scrollspeed * elapsed, 0.0f });
        }
        if (JamTemplate::InputManager::pressed(sf::Keyboard::W)) {
            getGame()->moveCam(sf::Vector2f { 0.0f, -scrollspeed * elapsed });
        } else if (JamTemplate::InputManager::pressed(sf::Keyboard::S)) {
            getGame()->moveCam(sf::Vector2f { 0.0f, scrollspeed * elapsed });
        }

        if (JamTemplate::InputManager::justPressed(sf::Keyboard::I)) {
            m_tilemap->setIgnoreCamMovement(true);
        }
        if (JamTemplate::InputManager::justPressed(sf::Keyboard::O)) {
            m_tilemap->setIgnoreCamMovement(false);
        }
    }
};
#endif
