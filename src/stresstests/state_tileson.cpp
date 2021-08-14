#include "state_tileson.hpp"
#include "game_interface.hpp"
#include "input_manager.hpp"
#include "sound.hpp"
#include "state_select.hpp"
#include "tilemap.hpp"
#include "timer.hpp"

void StateTileson::doInternalCreate()
{
    m_tilemap = std::make_shared<jt::Tilemap>("assets/tileson_test.json");
    m_tilemap->setScreenSizeHint(jt::Vector2(400, 300));

    m_sound = std::make_shared<jt::Sound>();
    m_sound->load("assets/test.ogg");

    auto const t = std::make_shared<jt::Timer>(2.5f, [sound = m_sound]() { sound->play(); });
    add(t);
}

void StateTileson::doInternalUpdate(float const elapsed)
{
    auto const scrollspeed = 50.0f;
    m_tilemap->update(elapsed);
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

    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->switchState(std::make_shared<StateSelect>());
    }
}

void StateTileson::doInternalDraw() const { m_tilemap->draw(getGame()->getRenderTarget()); }
