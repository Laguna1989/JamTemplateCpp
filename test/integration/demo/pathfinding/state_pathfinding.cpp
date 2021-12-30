#include "state_pathfinding.hpp"
#include "../state_select.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "pathfinder/node.hpp"
#include "random/random.hpp"

void StatePathfinding::doInternalCreate()
{
    createTiles();

    createNodeConnections();

    resetTiles();
    calculatePath(getTileAt(7, 3)->getNode(), getTileAt(7, 9)->getNode());
}

void StatePathfinding::calculatePath(jt::pathfinder::NodeT start, jt::pathfinder::NodeT end)
{
    auto path = jt::pathfinder::calculatePath(start, end);
    for (auto const& n : path) {
        auto const pos = n->getTilePosition();
        auto t = getTileAt(static_cast<int>(pos.x), static_cast<int>(pos.y));
        if (t) {
            t->getDrawable()->setColor(jt::colors::Cyan);
        }
    }
}

void StatePathfinding::createNodeConnections()
{
    for (auto& t : m_tiles) {
        if (t->getBlocked()) {
            continue;
        }
        auto const currentPos = t->getNode()->getTilePosition();

        for (int i = -1; i != 2; ++i) {
            for (int j = -1; j != 2; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }
                auto oi = static_cast<int>(currentPos.x + i);
                auto oj = static_cast<int>(currentPos.y + j);
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
            std::shared_ptr<jt::Shape> drawable = jt::dh::createShapeRect(
                jt::Vector2f { 19, 19 }, jt::colors::White, getGame()->gfx().textureManager());
            drawable->setPosition(jt::Vector2f { i * 20.0f, j * 20.0f });
            auto node = std::make_shared<jt::pathfinder::Node>();
            node->setPosition(
                jt::Vector2u { static_cast<unsigned int>(i), static_cast<unsigned int>(j) });

            auto t = std::make_shared<jt::tilemap::TileNode>(drawable, node, false);
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
}

void StatePathfinding::doInternalUpdate(float elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Space)) {
        resetTiles();
        calculatePath(
            getTileAt(jt::Random::getInt(0, mapSizeX - 1), jt::Random::getInt(0, mapSizeY - 1))
                ->getNode(),
            getTileAt(jt::Random::getInt(0, mapSizeX - 1), jt::Random::getInt(0, mapSizeY - 1))
                ->getNode());
    }

    for (auto& t : m_tiles) {
        t->getDrawable()->update(elapsed);
    }
}

void StatePathfinding::doInternalDraw() const
{
    for (auto& t : m_tiles) {
        t->getDrawable()->draw(getGame()->gfx().target());
    }
}

std::shared_ptr<jt::tilemap::TileNode> StatePathfinding::getTileAt(int x, int y)
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
        jt::Color color = t->getBlocked() ? jt::colors::Black : jt::colors::White;
        t->getDrawable()->setColor(color);
        t->reset();
    }
}
std::string StatePathfinding::getName() const { return "Pathfinding"; }
