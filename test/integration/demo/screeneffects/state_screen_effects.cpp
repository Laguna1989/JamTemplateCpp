#include "state_screen_effects.hpp"
#include "sprite_functions.hpp"
#include <game_interface.hpp>
#include <state_select.hpp>
#include <tilemap/tileson_loader.hpp>
#include <imgui.h>

void StateScreenEffects::doInternalCreate()
{
    jt::tilemap::TilesonLoader loader { getGame()->cache().getTilemapCache(),
        "assets/test/integration/demo/screeneffect_map.json" };
    std::vector<std::string> const layerNames { "ground", "water_edges", "rug", "shadows", "fence",
        "walls", "props" };

    for (auto const& layer : layerNames) {
        m_tileLayers.emplace_back(std::make_shared<jt::tilemap::TileLayer>(
            loader.loadTilesFromLayer(layer, textureManager(), "assets/test/integration/demo/")));
    }

    m_stars = std::make_shared<jt::Stars>(50U, jt::colors::White, jt::Vector2f { 400.0f, 300.0f });
    add(m_stars);

    m_bubbleSmoke = std::make_shared<jt::BubbleSmoke>();
    add(m_bubbleSmoke);

    m_vignette = std::make_shared<jt::Vignette>(jt::Vector2f { 400.0f, 300.0f });
    add(m_vignette);

    m_scanLines = std::make_shared<jt::ScanLines>(jt::Vector2f { 400.0f, 2.0f }, 150);
    add(m_scanLines);

    m_wind = std::make_shared<jt::WindParticles>(jt::Vector2f { 400.0f, 300.0f },
        std::vector<jt::Color> { jt::colors::Black, jt::colors::Gray, jt::colors::White });
    add(m_wind);

    m_clouds = std::make_shared<jt::Clouds>(jt::Vector2f { -9.0f, 5.0f });
    add(m_clouds);
    setAutoDraw(false);
}

void StateScreenEffects::doInternalUpdate(float elapsed)
{
    for (auto& l : m_tileLayers) {
        l->update(elapsed);
    }

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }

    m_stars->setCamMovementFactor(m_starsMovementFactor);

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
    m_stars->setEnabled(m_drawStars);
    m_wind->setEnabled(m_drawWind);
    m_wind->m_windSpeed = m_windStrength;
}

void StateScreenEffects::doInternalDraw() const
{
    m_stars->draw();
    if (m_drawLevel) {
        for (auto const& l : m_tileLayers) {
            l->draw(renderTarget());
        }
    }

    m_bubbleSmoke->draw();
    m_wind->draw();
    m_clouds->draw();
    m_vignette->draw();
    m_scanLines->draw();

    drawGui();
}

void StateScreenEffects::drawGui() const
{
    ImGui::Begin("Screen Effects");
    ImGui::Checkbox("stars", &m_drawStars);
    ImGui::SliderFloat("stars parallax", &m_starsMovementFactor, 0.0f, 1.5f, "%.1f");
    ImGui::Checkbox("level", &m_drawLevel);
    ImGui::Checkbox("clouds", &m_drawClouds);
    ImGui::Checkbox("vignette", &m_drawVignette);
    ImGui::Checkbox("scan lines", &m_drawScanLines);
    ImGui::Checkbox("wind", &m_drawWind);
    ImGui::SliderFloat("wind strength", &m_windStrength, 0.0f, 4.0f, "%.1f");
    if (ImGui::Button("bubbles")) {
        m_bubbleSmoke->fire(jt::Vector2f { 400.0f, 300.0f });
    }

    ImGui::End();
}
