#ifndef GUARD_JAMTEMPLATE_STATE_PATHFINDING_HPP
#define GUARD_JAMTEMPLATE_STATE_PATHFINDING_HPP

#include "game_state.hpp"
#include "pathfinder/node_interface.hpp"
#include "pathfinder/pathfinder.hpp"
#include "shape.hpp"
#include "tilemap/tile_node.hpp"

class StatePathfinding : public jt::GameState {
public:
    std::string getName() const override;

private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::vector<std::shared_ptr<jt::tilemap::TileNode>> m_tiles;

    std::shared_ptr<jt::tilemap::TileNode> getTileAt(int x, int y);

    int mapSizeX = 15;
    int mapSizeY = 14;
    void createTiles();
    void createNodeConnections();

    void resetTiles();
    void calculatePath(jt::pathfinder::NodeT start, jt::pathfinder::NodeT end);
};

#endif // GUARD_JAMTEMPLATE_STATE_PATHFINDING_HPP
