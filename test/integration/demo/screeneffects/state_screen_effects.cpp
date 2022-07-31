#include "state_screen_effects.hpp"
#include "sprite_functions.hpp"
#include <game_interface.hpp>
#include <state_select.hpp>
#include <tilemap/tileson_loader.hpp>
#include <imgui.h>

void StateScreenEffects::doInternalCreate()
{
    jt::tilemap::TilesonLoader loader { "assets/demos/screeneffects/map.json" };
    std::vector<std::string> const layerNames { "ground", "water_edges", "rug", "shadows", "fence",
        "walls", "props" };

    for (auto const& layer : layerNames) {
        m_tileLayers.emplace_back(std::make_shared<jt::tilemap::TileLayer>(
            loader.loadTilesFromLayer(layer, textureManager())));
    }

    m_vignette = std::make_shared<jt::Vignette>(jt::Vector2f { 400.0f, 300.0f });
    add(m_vignette);

    m_scanLines = std::make_shared<jt::ScanLines>(jt::Vector2f { 400.0f, 2.0f }, 150);
    add(m_scanLines);

    m_clouds = std::make_shared<jt::Clouds>(jt::Vector2f { -9.0f, 5.0f });
    add(m_clouds);
}

void StateScreenEffects::doInternalUpdate(float elapsed)
{
    for (auto& l : m_tileLayers) {
        l->update(elapsed);
    }

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }

    scroll(elapsed);
}

void StateScreenEffects::scroll(float elapsed)
{
    auto const keyboard = getGame()->input().keyboard();
    auto const scrollspeed = 150.0f;
    if (keyboard->pressed(jt::KeyCode::D)) {
        getGame()->gfx().camera().move(jt::Vector2f { scrollspeed * elapsed, 0.0f });
    } else if (keyboard->pressed(jt::KeyCode::A)) {
        getGame()->gfx().camera().move(jt::Vector2f { -scrollspeed * elapsed, 0.0f });
    }
    if (keyboard->pressed(jt::KeyCode::W)) {
        getGame()->gfx().camera().move(jt::Vector2f { 0.0f, -scrollspeed * elapsed });
    } else if (keyboard->pressed(jt::KeyCode::S)) {
        getGame()->gfx().camera().move(jt::Vector2f { 0.0f, scrollspeed * elapsed });
    }

    m_clouds->setEnabled(m_drawClouds);
    m_vignette->setEnabled(m_drawVignette);
    m_scanLines->setEnabled(m_drawScanLines);
}

void StateScreenEffects::doInternalDraw() const
{
    for (auto const& l : m_tileLayers) {
        l->draw(renderTarget());
    }

    drawGui();
    drawObjects();
}

void StateScreenEffects::drawGui() const
{
    ImGui::Begin("Screen Effects");
    ImGui::Checkbox("clouds", &m_drawClouds);
    ImGui::Checkbox("vignette", &m_drawVignette);
    ImGui::Checkbox("scan lines", &m_drawScanLines);
    ImGui::End();
}
