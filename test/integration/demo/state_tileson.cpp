#include "state_tileson.hpp"
#include "game_interface.hpp"
#include "input/input_manager.hpp"
#include "shape.hpp"
#include "sound.hpp"
#include "state_select.hpp"
#include "tilemap/tile_layer.hpp"
#include "tilemap/tilemap_helpers.hpp"
#include "timer.hpp"
#include <pathfinder/pathfinder.hpp>

void StateTileson::doInternalCreate()
{
    m_tileLayerGround = std::make_shared<jt::tilemap::TileLayer>(
        "assets/tileson_test.json", "ground", getGame()->getTextureManager());
    m_tileLayerGround->setScreenSizeHint(jt::Vector2(400, 300));

    m_tileLayerOverlay = std::make_shared<jt::tilemap::TileLayer>(
        "assets/tileson_test.json", "overlay", getGame()->getTextureManager());
    m_tileLayerOverlay->setScreenSizeHint(jt::Vector2(400, 300));

    m_objectsLayer
        = std::make_shared<jt::tilemap::ObjectLayer>("assets/tileson_test.json", "objects");

    m_nodeLayer = std::make_shared<jt::tilemap::NodeLayer>(
        "assets/tileson_test.json", "ground", getGame()->getTextureManager());
    for (auto& t : m_nodeLayer->getAllTiles()) {
        add(t);
    }

    m_actor = std::make_shared<Actor>();

    add(m_actor);
    m_actor->setPosition(jt::Vector2u { 5, 6 });
    setAutoDraw(false);
}

void StateTileson::doInternalUpdate(float const elapsed)
{

    m_tileLayerGround->update(elapsed);

    m_tileLayerOverlay->update(elapsed);

    moveCamera(elapsed);

    toggleVisibility();

    if (getGame()->input()->mouse()->justPressed(jt::MouseButtonCode::MBLeft)) {
        auto const actorPos
            = jt::Vector2u { static_cast<unsigned int>(m_actor->getFinalPosition().x() / 32.0f),
                  static_cast<unsigned int>(m_actor->getFinalPosition().y() / 32.0f) };

        auto const mpos = getGame()->input()->mouse()->getMousePositionWorld();
        auto const tileEndPos = jt::Vector2u { static_cast<unsigned int>(mpos.x() / 32.0f),
            static_cast<unsigned int>(mpos.y() / 32.0f) };

        calculatePath(m_nodeLayer->getTileAt(actorPos.x(), actorPos.y())->getNode(),
            m_nodeLayer->getTileAt(tileEndPos.x(), tileEndPos.y())->getNode());
    }

    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager()->switchState(std::make_shared<StateSelect>());
    }
}
void StateTileson::toggleVisibility()
{
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::Num1)) {
        m_drawTileLayer1 = !m_drawTileLayer1;
    }
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::Num2)) {
        m_drawTileLayer2 = !m_drawTileLayer2;
    }
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::Num3)) {
        m_drawObjects = !m_drawObjects;
    }
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::Num4)) {
        m_drawTileNodes = !m_drawTileNodes;
    }
}

void StateTileson::moveCamera(float const elapsed)
{
    auto const scrollspeed = 150.0f;
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
        t->draw();
    }
}
void StateTileson::drawTileLayers() const
{
    if (m_drawTileLayer1) {
        m_tileLayerGround->draw(getGame()->getRenderTarget());
    }

    if (m_drawTileLayer2) {
        m_tileLayerOverlay->draw(getGame()->getRenderTarget());
    }
}
void StateTileson::drawObjectLayer() const
{
    if (!m_drawObjects) {
        return;
    }
    for (auto& obj : m_objectsLayer->getObjects()) {

        auto shape = jt::tilemap::createShapeFrom(obj, getGame()->getTextureManager());
        shape->draw(getGame()->getRenderTarget());
    }
}

void StateTileson::calculatePath(jt::pathfinder::NodeT start, jt::pathfinder::NodeT end)
{
    m_nodeLayer->reset();
    auto path = jt::pathfinder::calculatePath(start, end);
    for (auto const& n : path) {
        auto const pos = n->getTilePosition();
        auto t = m_nodeLayer->getTileAt(static_cast<int>(pos.x()), static_cast<int>(pos.y()));
        if (t) {
            t->setColor(jt::colors::Cyan);
        }
    }

    m_actor->setPath(path);
}
