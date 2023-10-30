#include "state_tilemap_effects.hpp"
#include <color/palette.hpp>
#include <color/palette_builder.hpp>
#include <game_interface.hpp>
#include <input/input_manager.hpp>
#include <pathfinder/pathfinder.hpp>
#include <state_select.hpp>
#include <tilemap/tile_layer.hpp>
#include <tilemap/tilemap_cache.hpp>
#include <tilemap/tilemap_helpers.hpp>
#include <tilemap/tileson_loader.hpp>
#include <timer.hpp>
#include <imgui.h>

void StateTilemapEffects::onCreate()
{
    jt::tilemap::TilesonLoader loader { getGame()->cache().getTilemapCache(),
        "assets/test/integration/demo/tilemap_onebit.json" };

    m_tileLayerGround = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("ground", textureManager(), "assets/test/integration/demo/"));
    m_tileLayerGround->setScreenSizeHint(jt::Vector2f { 400, 300 });
    m_tileLayerGround->setOriginInternal(jt::Vector2f { 8.0f, 8.0f });
    setAutoDraw(false);
}

void StateTilemapEffects::onEnter() { }

void StateTilemapEffects::onUpdate(float const elapsed)
{
    m_tileLayerGround->setRotation(m_rotation);
    m_tileLayerGround->setScale(jt::Vector2f { m_scaleX, m_scaleY });
    m_tileLayerGround->update(elapsed);
    m_time = getAge();

    moveCamera(elapsed);

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateTilemapEffects::moveCamera(float const elapsed)
{
    auto const scrollspeed = 150.0f;
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::D)) {
        getGame()->gfx().camera().move(jt::Vector2f { scrollspeed * elapsed, 0.0f });
    } else if (getGame()->input().keyboard()->pressed(jt::KeyCode::A)) {
        getGame()->gfx().camera().move(jt::Vector2f { -scrollspeed * elapsed, 0.0f });
    }
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::W)) {
        getGame()->gfx().camera().move(jt::Vector2f { 0.0f, -scrollspeed * elapsed });
    } else if (getGame()->input().keyboard()->pressed(jt::KeyCode::S)) {
        getGame()->gfx().camera().move(jt::Vector2f { 0.0f, scrollspeed * elapsed });
    }
}

void StateTilemapEffects::onDraw() const
{
    drawObjects();
    m_tileLayerGround->draw(renderTarget());

    ImGui::Begin("Tilemap Effects");
    if (ImGui::Button("Shake")) {
        m_tileLayerGround->shake(0.5f, 5.5f);
    }

    ImGui::Separator();
    ImGui::SliderFloat("rotation", &m_rotation, 0.0f, 360.0f, "%.0f");

    ImGui::Separator();
    ImGui::SliderFloat("scale X", &m_scaleX, 0.0f, 2.0f, "%.1f");
    ImGui::SliderFloat("scale Y", &m_scaleY, 0.0f, 2.0f, "%.1f");

    ImGui::Separator();
    if (ImGui::Button("Colorize X+Y")) {
        auto const numberOfColors = 360u;
        jt::PaletteBuilder builder;
        m_tileLayerGround->setColorFunction(
            [&t = m_time,
                palette = builder.addGradientH(0, 360, 100.0, 100.0f, numberOfColors).create()](
                jt::Vector2f const& pos) {
                auto const positionScale = 9;
                auto const timeScale = 120.0f;
                auto const index = static_cast<std::size_t>(
                                       (pos.x / 16 + pos.y / 16) * positionScale + t * timeScale)
                    % palette.size();
                return palette.getColor(index);
            });
    }

    if (ImGui::Button("Colorize Rad")) {
        auto const numberOfColors = 360u;
        jt::PaletteBuilder builder;
        m_tileLayerGround->setColorFunction(
            [&t = m_time,
                palette = builder.addGradientH(0, 360, 100.0, 100.0f, numberOfColors).create()](
                jt::Vector2f const& pos) {
                jt::Vector2f const center { 8.0f * 16.0f, 8.0f * 16.0f };
                auto dist = pos - center;
                if (dist.x < 0) {
                    dist.x = -dist.x;
                }
                if (dist.y < 0) {
                    dist.y = -dist.y;
                }
                auto const positionScale = 9;
                auto const timeScale = 120.0f;
                auto const index = static_cast<std::size_t>(
                                       (dist.x / 16 + dist.y / 16) * positionScale + t * timeScale)
                    % palette.size();
                return palette.getColor(index);
            });
    }
    ImGui::End();
}

std::string StateTilemapEffects::getName() const { return "Tile Effects"; }
