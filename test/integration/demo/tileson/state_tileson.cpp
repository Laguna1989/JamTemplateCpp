#include "state_tileson.hpp"
#include "../state_select.hpp"
#include "game_interface.hpp"
#include "input/input_manager.hpp"
#include "pathfinder/pathfinder.hpp"
#include "tilemap/tile_layer.hpp"
#include "tilemap/tilemap_helpers.hpp"
#include "tilemap/tilemap_manager_tileson_impl.hpp"
#include "tilemap/tileson_loader.hpp"
#include "timer.hpp"

void StateTileson::doInternalCreate()
{
    jt::tilemap::TilesonLoader loader { "assets/tileson_test.json" };

    m_tileLayerGround = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("ground", getGame()->gfx().textureManager()));
    m_tileLayerGround->setScreenSizeHint(jt::Vector2f { 400, 300 });

    m_tileLayerOverlay = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("overlay", getGame()->gfx().textureManager()));
    m_tileLayerOverlay->setScreenSizeHint(jt::Vector2f { 400, 300 });

    m_objectsLayer
        = std::make_shared<jt::tilemap::ObjectLayer>(loader.loadObjectsFromLayer("objects"));

    m_nodeLayer = std::make_shared<jt::tilemap::NodeLayer>(
        loader.loadNodesFromLayer("ground", getGame()->gfx().textureManager()));

    m_actor = std::make_shared<Actor>();

    add(m_actor);
    m_actor->setPosition(jt::Vector2u { 5, 6 });
    setAutoDraw(false);
}

void StateTileson::doInternalUpdate(float const elapsed)
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

        calculatePath(m_nodeLayer->getTileAt(actorPos.x, actorPos.y)->getNode(),
            m_nodeLayer->getTileAt(tileEndPos.x, tileEndPos.y)->getNode());
    }

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
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

void StateTileson::doInternalDraw() const
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
        t->getDrawable()->draw(getGame()->gfx().target());
    }
}
void StateTileson::drawTileLayers() const
{
    if (m_drawTileLayer1) {
        m_tileLayerGround->draw(getGame()->gfx().target());
    }

    if (m_drawTileLayer2) {
        m_tileLayerOverlay->draw(getGame()->gfx().target());
    }
}
void StateTileson::drawObjectLayer() const
{
    if (!m_drawObjects) {
        return;
    }
    for (auto& obj : m_objectsLayer->getObjects()) {
        auto shape = jt::tilemap::createShapeFrom(obj, getGame()->gfx().textureManager());
        shape->draw(getGame()->gfx().target());
    }
}

void StateTileson::calculatePath(jt::pathfinder::NodeT start, jt::pathfinder::NodeT end)
{
    m_nodeLayer->reset();
    auto path = jt::pathfinder::calculatePath(start, end);
    for (auto const& n : path) {
        auto const pos = n->getTilePosition();
        auto t = m_nodeLayer->getTileAt(static_cast<int>(pos.x), static_cast<int>(pos.y));
        if (t) {
            t->getDrawable()->setColor(jt::colors::Cyan);
        }
    }

    m_actor->setPath(path);
}
std::string StateTileson::getName() const { return "Tilemap"; }
