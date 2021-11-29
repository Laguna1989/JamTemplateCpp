#ifndef GUARD_JAMTEMAPLTE_NODE_HPP
#define GUARD_JAMTEMAPLTE_NODE_HPP

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

    jt::Vector2u getTilePosition() const override;

    void setPosition(jt::Vector2u pos);

    void addNeighbour(std::weak_ptr<NodeInterface> other) override;

    float getValue() override;
    void setValue(float value) override;

private:
    bool m_visited { false };
    float m_value { -1.0f };
    jt::Vector2u m_position;
    std::vector<std::weak_ptr<jt::pathfinder::NodeInterface>> m_neighbours;
};
} // namespace pathfinder
} // namespace jt
#endif // GUARD_JAMTEMAPLTE_NODE_HPP
