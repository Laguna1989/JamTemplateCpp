#include "state_tileson.hpp"
#include "timer.hpp"
#include <game_interface.hpp>
#include <input/input_manager.hpp>
#include <pathfinder/pathfinder.hpp>
#include <state_select.hpp>
#include <tilemap/tile_layer.hpp>
#include <tilemap/tilemap_cache.hpp>
#include <tilemap/tilemap_helpers.hpp>
#include <tilemap/tileson_loader.hpp>

void StateTileson::onCreate()
{
    jt::tilemap::TilesonLoader loader { getGame()->cache().getTilemapCache(),
        "assets/test/integration/demo/tileson_test.json" };

    m_tileLayerGround = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("ground", textureManager(), "assets/test/integration/demo/"));
    m_tileLayerGround->setScreenSizeHint(jt::Vector2f { 400, 300 });

    m_tileLayerOverlay = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("overlay", textureManager(), "assets/test/integration/demo/"));
    m_tileLayerOverlay->setScreenSizeHint(jt::Vector2f { 400, 300 });

    m_objectsLayer
        = std::make_shared<jt::tilemap::ObjectLayer>(loader.loadObjectsFromLayer("objects"));

    m_nodeLayer = std::make_shared<jt::tilemap::NodeLayer>(
        loader.loadTileNodesFromLayer("ground", textureManager()));

    m_actor = std::make_shared<Actor>();

    add(m_actor);
    setAutoDraw(false);
}

void StateTileson::onEnter() { m_actor->setPosition(jt::Vector2u { 5, 6 }); }

void StateTileson::onUpdate(float const elapsed)
{

    m_tileLayerGround->update(elapsed);

    m_tileLayerOverlay->update(elapsed);

    for (auto& t : m_nodeLayer->getAllTiles()) {
        t->getDrawable()->update(elapsed);
    }

    moveCamera(elapsed);

    toggleVisibility();

    if (getGame()->input().mouse()->justPressed(jt::MouseButtonCode::MBLeft)) {
        auto const actorPos
            = jt::Vector2u { static_cast<unsigned int>(m_actor->getFinalPosition().x / 32.0f),
                  static_cast<unsigned int>(m_actor->getFinalPosition().y / 32.0f) };

        auto const mpos = getGame()->input().mouse()->getMousePositionWorld();
        auto const tileEndPos = jt::Vector2u { static_cast<unsigned int>(mpos.x / 32.0f),
            static_cast<unsigned int>(mpos.y / 32.0f) };

        calculatePath(m_nodeLayer->getTileAt(actorPos)->getNode(),
            m_nodeLayer->getTileAt(tileEndPos)->getNode());
    }

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}
void StateTileson::toggleVisibility()
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Num1)) {
        m_drawTileLayer1 = !m_drawTileLayer1;
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Num2)) {
        m_drawTileLayer2 = !m_drawTileLayer2;
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Num3)) {
        m_drawObjects = !m_drawObjects;
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Num4)) {
        m_drawTileNodes = !m_drawTileNodes;
    }
}

void StateTileson::moveCamera(float const elapsed)
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

void StateTileson::onDraw() const
{
    drawObjects();
    drawTileLayers();

    drawObjectLayer();

    m_actor->draw();
    drawNodeLayer();
}
void StateTileson::drawNodeLayer() const
{
    if (!m_drawTileNodes) {
        return;
    }
    for (auto& t : m_nodeLayer->getAllTiles()) {
        t->getDrawable()->draw(renderTarget());
    }
}
void StateTileson::drawTileLayers() const
{
    if (m_drawTileLayer1) {
        m_tileLayerGround->draw(renderTarget());
    }

    if (m_drawTileLayer2) {
        m_tileLayerOverlay->draw(renderTarget());
    }
}
void StateTileson::drawObjectLayer() const
{
    if (!m_drawObjects) {
        return;
    }
    for (auto& obj : m_objectsLayer->getObjects()) {
        auto shape = jt::tilemap::createShapeFrom(obj, textureManager());
        shape->draw(renderTarget());
    }
}

void StateTileson::calculatePath(jt::pathfinder::NodeT start, jt::pathfinder::NodeT end)
{
    m_nodeLayer->reset();
    auto path = jt::pathfinder::calculatePath(start, end);
    for (auto const& n : path) {
        auto t = m_nodeLayer->getTileAt(n->getTilePosition());
        if (t) {
            t->getDrawable()->setColor(jt::colors::Cyan);
        }
    }

    m_actor->setPath(path);
}
std::string StateTileson::getName() const { return "Tilemap"; }
