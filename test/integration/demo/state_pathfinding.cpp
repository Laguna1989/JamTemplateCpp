#include "state_pathfinding.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "pathfinder/node.hpp"
#include "pathfinder/pathfindinder.hpp"
#include "state_select.hpp"
#include <random.hpp>

Tile::Tile(jt::Vector2 pos, bool blocked)
{
    auto node = std::make_shared<jt::pathfinder::Node>();
    node->setPosition(pos);
    m_node = node;
    m_blocked = blocked;
}
void Tile::doCreate()
{
    m_shape = jt::dh::createShapeRect({ 19, 19 });
    if (m_blocked) {
        m_shape->setColor(jt::colors::Black);
    }
}
void Tile::doUpdate(float const elapsed)
{
    m_shape->setPosition(getPosition() * 20.0f);
    m_shape->update(elapsed);
}
void Tile::doDraw() const { m_shape->draw(getGame()->getRenderTarget()); }

std::shared_ptr<jt::pathfinder::NodeInterface> Tile::getNode() { return m_node; }

jt::Vector2 Tile::getPosition() { return m_node->getPosition(); }
void Tile::setBlocked(bool blocked) { m_blocked = blocked; }
bool Tile::getBlocked() { return m_blocked; }
void Tile::setColor(jt::Color const& c) { m_shape->setColor(c); }
void Tile::reset()
{
    m_node->setValue(-1);
    m_node->unvisit();
    setColor(jt::colors::White);
    if (m_blocked) {
        m_shape->setColor(jt::colors::Black);
    }
}

void StatePathfinding::doInternalCreate()
{
    createTiles();

    createNodeConnections();

    calculatePath(getTileAt(7, 3)->getNode(), getTileAt(7, 9)->getNode());
}
void StatePathfinding::calculatePath(jt::pathfinder::NodeT start, jt::pathfinder::NodeT end)
{
    auto path = jt::pathfinder::calculatePath(start, end);
    for (auto const& n : path) {
        auto const pos = n->getPosition();
        auto t = getTileAt(static_cast<int>(pos.x()), static_cast<int>(pos.y()));
        if (t) {
            t->setColor(jt::colors::Cyan);
        }
    }
}
void StatePathfinding::createNodeConnections()
{
    for (auto& t : m_tiles) {
        if (t->getBlocked()) {
            continue;
        }
        auto const currentPos = t->getPosition();

        for (int i = -1; i != 2; ++i) {
            for (int j = -1; j != 2; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }
                auto oi = static_cast<int>(currentPos.x() + i);
                auto oj = static_cast<int>(currentPos.y() + j);
                auto ot = getTileAt(oi, oj);
                if (ot) {
                    if (ot->getBlocked()) {
                        continue;
                    }
                    t->getNode()->addNeighbour(ot->getNode());
                }
            }
        }
    }
}
void StatePathfinding::createTiles()
{
    for (int i = 0; i != mapSizeX; ++i) {
        for (int j = 0; j != mapSizeY; ++j) {
            auto t = std::make_shared<Tile>(
                jt::Vector2 { static_cast<float>(i), static_cast<float>(j) }, false);
            m_tiles.push_back(t);
        }
    }

    for (int i = 5; i != 10; ++i) {
        getTileAt(i, 6)->setBlocked(true);
    }
    getTileAt(5, 0)->setBlocked(true);
    getTileAt(5, 1)->setBlocked(true);
    getTileAt(5, 2)->setBlocked(true);
    getTileAt(5, 3)->setBlocked(true);
    getTileAt(5, 4)->setBlocked(true);
    getTileAt(5, 5)->setBlocked(true);

    getTileAt(9, 5)->setBlocked(true);

    for (auto& t : m_tiles) {
        add(t);
    }
}
void StatePathfinding::doInternalUpdate(float /*elapsed*/)
{
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager()->switchState(std::make_shared<StateSelect>());
    }

    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::Space)) {
        resetTiles();
        calculatePath(
            getTileAt(jt::Random::getInt(0, mapSizeX - 1), jt::Random::getInt(0, mapSizeY - 1))
                ->getNode(),
            getTileAt(jt::Random::getInt(0, mapSizeX - 1), jt::Random::getInt(0, mapSizeY - 1))
                ->getNode());
    }
}
void StatePathfinding::doInternalDraw() const { }

std::shared_ptr<Tile> StatePathfinding::getTileAt(int x, int y)
{
    if (x < 0) {
        return nullptr;
    }
    if (y < 0) {
        return nullptr;
    }
    if (x >= mapSizeX) {
        return nullptr;
    }
    if (y >= mapSizeY) {
        return nullptr;
    }
    int const index = y + x * mapSizeY;
    if (static_cast<std::size_t>(index) >= m_tiles.size()) {
        return nullptr;
    }
    return m_tiles.at(index);
}

void StatePathfinding::resetTiles()
{
    for (auto& t : m_tiles) {
        t->reset();
    }
}
