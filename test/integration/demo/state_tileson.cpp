#include "state_tileson.hpp"
#include "game_interface.hpp"
#include "input_manager.hpp"
#include "sound.hpp"
#include "state_select.hpp"
#include "tilemap/tilelayer.hpp"
#include "timer.hpp"

void StateTileson::doInternalCreate()
{
    m_tilemap = std::make_shared<jt::tilemap::TileLayer>("assets/tileson_test.json");
    m_tilemap->setScreenSizeHint(jt::Vector2(400, 300));

    //    for (auto t : m_tilemap->getAllTiles()) {
    //        add(t);
    //    }

    setAutoDraw(false);
}

void StateTileson::doInternalUpdate(float const elapsed)
{
    auto const scrollspeed = 150.0f;
    m_tilemap->update(elapsed);

    moveCamera(elapsed, scrollspeed);

    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager()->switchState(std::make_shared<StateSelect>());
    }
}

void StateTileson::moveCamera(float const elapsed, float const scrollspeed)
{
    if (getGame()->input()->keyboard()->pressed(jt::KeyCode::D)) {
        getGame()->getCamera()->move(jt::Vector2 { scrollspeed * elapsed, 0.0f });
    } else if (getGame()->input()->keyboard()->pressed(jt::KeyCode::A)) {
        getGame()->getCamera()->move(jt::Vector2 { -scrollspeed * elapsed, 0.0f });
    }
    if (getGame()->input()->keyboard()->pressed(jt::KeyCode::W)) {
        getGame()->getCamera()->move(jt::Vector2 { 0.0f, -scrollspeed * elapsed });
    } else if (getGame()->input()->keyboard()->pressed(jt::KeyCode::S)) {
        getGame()->getCamera()->move(jt::Vector2 { 0.0f, scrollspeed * elapsed });
    }
}

void StateTileson::doInternalDraw() const
{
    m_tilemap->draw(getGame()->getRenderTarget());
    //    for (auto t : m_tilemap->getAllTiles()) {
    //        t->draw();
    //    }
    //    drawObjects();
}
