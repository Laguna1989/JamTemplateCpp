#ifndef GUARD_JAMTEMPLATE_STATE_PATHFINDING_HPP
#define GUARD_JAMTEMPLATE_STATE_PATHFINDING_HPP

#include "game_state.hpp"
#include "pathfinder/node_interface.hpp"
#include "pathfinder/pathfindinder.hpp"
#include "shape.hpp"

class Tile : public jt::GameObject {
public:
    Tile(jt::Vector2 pos, bool blocked);

    std::shared_ptr<jt::pathfinder::NodeInterface> getNode();
    jt::Vector2 getPosition();
    void setBlocked(bool blocked);
    bool getBlocked();
    void reset();

    void setColor(jt::Color const& c);

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    std::shared_ptr<jt::Shape> m_shape;
    std::shared_ptr<jt::pathfinder::NodeInterface> m_node;
    bool m_blocked { false };
};

class StatePathfinding : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::vector<std::shared_ptr<Tile>> m_tiles;

    std::shared_ptr<Tile> getTileAt(int x, int y);

    int mapSizeX = 15;
    int mapSizeY = 14;
    void createTiles();
    void createNodeConnections();

    void resetTiles();
    void calculatePath(jt::pathfinder::NodeT start, jt::pathfinder::NodeT end);
};

#endif // GUARD_JAMTEMPLATE_STATE_PATHFINDING_HPP
