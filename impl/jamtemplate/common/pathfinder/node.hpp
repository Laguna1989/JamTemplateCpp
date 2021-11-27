#ifndef MYAWESOMEGAME_NODE_HPP
#define MYAWESOMEGAME_NODE_HPP

#include "node_interface.hpp"
#include <memory>
#include <vector>

namespace jt {
namespace pathfinder {
class Node : public NodeInterface {
public:
    std::vector<std::weak_ptr<NodeInterface>> getNeighbours() override;

    void visit() override;
    void unvisit() override;
    bool wasVisited() override;

    jt::Vector2 getPosition() const override;

    void setPosition(jt::Vector2 pos);

    void addNeighbour(std::weak_ptr<NodeInterface> other) override;

    float getValue() override;
    void setValue(float value) override;

private:
    bool m_visited { false };
    float m_value { -1.0f };
    jt::Vector2 m_position;
    std::vector<std::weak_ptr<jt::pathfinder::NodeInterface>> m_neighbours;
};
} // namespace pathfinder
} // namespace jt
#endif // MYAWESOMEGAME_NODE_HPP
