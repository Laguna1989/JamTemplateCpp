#include "StateTileson.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "SmartTilemap.hpp"
#include "StateBox2d.hpp"
#include "Timer.hpp"
#include <filesystem>

void StateTileson::doInternalCreate()
{
    m_tilemap = std::make_shared<jt::SmartTilemap>("assets/tileson_test.json");
    m_tilemap->setScreenSizeHint(jt::Vector2(400, 300), getGame());

    m_sound = std::make_shared<jt::Sound>();
    m_sound->load("assets/test.ogg");

    auto const t = std::make_shared<jt::Timer>(2.5f, [sound = m_sound]() { sound->play(); });
    add(t);
}

void StateTileson::doInternalUpdate(float const elapsed)
{
    auto const scrollspeed = 50.0f;
    m_tilemap->update(elapsed);
    if (jt::InputManager::pressed(jt::KeyCode::D)) {
        getGame()->moveCam(jt::Vector2 { scrollspeed * elapsed, 0.0f });
    } else if (jt::InputManager::pressed(jt::KeyCode::A)) {
        getGame()->moveCam(jt::Vector2 { -scrollspeed * elapsed, 0.0f });
    }
    if (jt::InputManager::pressed(jt::KeyCode::W)) {
        getGame()->moveCam(jt::Vector2 { 0.0f, -scrollspeed * elapsed });
    } else if (jt::InputManager::pressed(jt::KeyCode::S)) {
        getGame()->moveCam(jt::Vector2 { 0.0f, scrollspeed * elapsed });
    }

    if (jt::InputManager::justPressed(jt::KeyCode::F1)) {
        getGame()->switchState(std::make_shared<StateBox2d>());
    }
}

void StateTileson::doInternalDraw() const { m_tilemap->draw(getGame()->getRenderTarget()); }
