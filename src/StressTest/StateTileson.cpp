#include "StateTileson.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "SmartTilemap.hpp"
#include "StateBox2d.hpp"
#include <filesystem>

void StateTileson::doCreate()
{
    m_tilemap = std::make_shared<JamTemplate::SmartTilemap>(
        std::filesystem::path("assets/tileson_test.json"));
    m_tilemap->setScreenSizeHint(sf::Vector2f(400, 300), getGame());
}

void StateTileson::doDraw() const { m_tilemap->draw(getGame()->getRenderTarget()); }

void StateTileson::doUpdate(float const elapsed)
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

    if (JamTemplate::InputManager::justPressed(sf::Keyboard::F1)) {
        getGame()->switchState(std::make_shared<StateBox2d>());
    }
}
