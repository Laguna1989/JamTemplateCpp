#include "StateTileson.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
// #include "SmartTilemap.hpp"
#include "StateBox2d.hpp"
#include <filesystem>

void StateTileson::doCreate()
{
    // m_tilemap = std::make_shared<jt::SmartTilemap>(
    //     std::filesystem::path("assets/tileson_test.json"));
    // m_tilemap->setScreenSizeHint(jt::vector2(400, 300), getGame());
}

void StateTileson::doDraw() const
{ /*m_tilemap->draw(getGame()->getRenderTarget());*/
}

void StateTileson::doUpdate(float const elapsed)
{
    // TODO
    // auto const scrollspeed = 50.0f;
    // m_tilemap->update(elapsed);
    // if (jt::InputManager::pressed(jt::KeyCode::D)) {
    //     getGame()->moveCam(jt::vector2 { scrollspeed * elapsed, 0.0f });
    // } else if (jt::InputManager::pressed(jt::KeyCode::A)) {
    //     getGame()->moveCam(jt::vector2 { -scrollspeed * elapsed, 0.0f });
    // }
    // if (jt::InputManager::pressed(jt::KeyCode::W)) {
    //     getGame()->moveCam(jt::vector2 { 0.0f, -scrollspeed * elapsed });
    // } else if (jt::InputManager::pressed(jt::KeyCode::S)) {
    //     getGame()->moveCam(jt::vector2 { 0.0f, scrollspeed * elapsed });
    // }

    // if (jt::InputManager::justPressed(jt::KeyCode::I)) {
    //     m_tilemap->setIgnoreCamMovement(true);
    // }
    // if (jt::InputManager::justPressed(jt::KeyCode::O)) {
    //     m_tilemap->setIgnoreCamMovement(false);
    // }

    if (jt::InputManager::justPressed(jt::KeyCode::F1)) {
        getGame()->switchState(std::make_shared<StateBox2d>());
    }
}
