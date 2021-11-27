#ifndef GUARD_JAMTEMPLATE_STATE_PATHFINDING_HPP
#define GUARD_JAMTEMPLATE_STATE_PATHFINDING_HPP

#include "game_state.hpp"
#include "pathfinder/node_interface.hpp"
#include "pathfinder/pathfindinder.hpp"
#include "shape.hpp"
#include "tilemap/tile.hpp"

class StatePathfinding : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::vector<std::shared_ptr<jt::Tile>> m_tiles;

    std::shared_ptr<jt::Tile> getTileAt(int x, int y);

    int mapSizeX = 15;
    int mapSizeY = 14;
    void createTiles();
    void createNodeConnections();

    void resetTiles();
    void calculatePath(jt::pathfinder::NodeT start, jt::pathfinder::NodeT end);
};

#endif // GUARD_JAMTEMPLATE_STATE_PATHFINDING_HPP
