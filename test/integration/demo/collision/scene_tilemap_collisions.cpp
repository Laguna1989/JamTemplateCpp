#include "scene_tilemap_collisions.hpp"
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <math_helper.hpp>
#include <tilemap/tileson_loader.hpp>
#include <array>
#include <string>

namespace {
constexpr float tileSize { 8.0f };
constexpr jt::Color hoverColor { 255, 255, 0, 200 };
constexpr std::array colliderColors { jt::Color { 230, 60, 60, 140 },
    jt::Color { 60, 200, 90, 140 }, jt::Color { 70, 120, 230, 140 },
    jt::Color { 220, 120, 220, 140 } };
} // namespace

void SceneTilemapCollisions::doCreate()
{
    jt::tilemap::TilesonLoader loader { getGame()->cache().getTilemapCache(),
        "assets/test/integration/demo/platformer_0_0.json" };

    m_tileLayer = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("ground", textureManager(), "assets/test/integration/demo/"));
    m_tileLayer->setScreenSizeHint(jt::Vector2f { 400.0f, 300.0f });

    // One rect per tile with the "blocked" property
    auto collisions = loader.loadCollisionsFromLayer("ground");
    m_rawColliders = createColliderSet(collisions.getRects());

    // Neighbouring tiles merged into larger rects
    collisions.refineColliders(tileSize);
    m_refinedColliders = createColliderSet(collisions.getRects());

    m_info = jt::dh::createText(renderTarget(), "", 12);
    m_info->setTextAlign(jt::Text::TextAlign::LEFT);
    m_info->setPosition(jt::Vector2f { 4.0f, 282.0f });
    m_info->setShadow(jt::colors::Black, jt::Vector2f { 1.0f, 1.0f });
}

SceneTilemapCollisions::ColliderSet SceneTilemapCollisions::createColliderSet(
    std::vector<jt::Rectf> const& rects) const
{
    ColliderSet set { rects, {}, {} };
    for (auto i = 0u; i != rects.size(); ++i) {
        auto const& r = rects[i];
        auto const color = colliderColors[i % colliderColors.size()];
        // shrink by one pixel so that neighbouring rects stay distinguishable
        auto shape = jt::dh::createShapeRect(
            jt::Vector2f { r.width - 1.0f, r.height - 1.0f }, color, textureManager());
        shape->setPosition(jt::Vector2f { r.left, r.top });
        set.shapes.push_back(shape);
        set.colors.push_back(color);
    }
    return set;
}

SceneTilemapCollisions::ColliderSet& SceneTilemapCollisions::activeColliders()
{
    return m_showRefined ? m_refinedColliders : m_rawColliders;
}

SceneTilemapCollisions::ColliderSet const& SceneTilemapCollisions::activeColliders() const
{
    return m_showRefined ? m_refinedColliders : m_rawColliders;
}

void SceneTilemapCollisions::doUpdate(float const elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Space)) {
        m_showRefined = !m_showRefined;
    }

    m_tileLayer->update(elapsed);

    auto const mousePosition = mouse()->getMousePositionWorld();
    auto& colliders = activeColliders();
    for (auto i = 0u; i != colliders.rects.size(); ++i) {
        bool const isHovered = jt::MathHelper::checkIsIn(colliders.rects[i], mousePosition);
        colliders.shapes[i]->setColor(isHovered ? hoverColor : colliders.colors[i]);
        colliders.shapes[i]->update(elapsed);
    }

    m_info->setText(std::string { "Space: toggle. " } + (m_showRefined ? "Refined: " : "Raw: ")
        + std::to_string(colliders.rects.size()) + " rects (raw "
        + std::to_string(m_rawColliders.rects.size()) + ", refined "
        + std::to_string(m_refinedColliders.rects.size()) + ")");
    m_info->update(elapsed);
}

void SceneTilemapCollisions::doDraw() const
{
    m_tileLayer->draw(renderTarget());
    for (auto const& shape : activeColliders().shapes) {
        shape->draw(renderTarget());
    }
    m_info->draw(renderTarget());
}

std::string SceneTilemapCollisions::getName() const { return "jt::TilemapCollisions"; }
