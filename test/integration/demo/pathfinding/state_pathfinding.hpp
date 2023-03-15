#ifndef JAMTEMPLATE_STATE_PATHFINDING_HPP
#define JAMTEMPLATE_STATE_PATHFINDING_HPP

#include <game_state.hpp>
#include <pathfinder/node_interface.hpp>
#include <pathfinder/pathfinder.hpp>
#include <shape.hpp>
#include <tilemap/tile_node.hpp>

class StatePathfinding : public jt::GameState {
public:
    std::string getName() const override;

private:
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    std::vector<std::shared_ptr<jt::tilemap::TileNode>> m_tiles;

    std::shared_ptr<jt::tilemap::TileNode> getTileAt(int x, int y);

    int mapSizeX = 15;
    int mapSizeY = 14;
    void createTiles();
    void createNodeConnections();

    void resetTiles();
    void calculatePath(jt::pathfinder::NodeT start, jt::pathfinder::NodeT end);
};

#endif // JAMTEMPLATE_STATE_PATHFINDING_HPP
