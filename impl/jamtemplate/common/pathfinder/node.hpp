#ifndef JAMTEMPLATE_NODE_HPP
#define JAMTEMPLATE_NODE_HPP

#include <pathfinder/node_interface.hpp>
#include <memory>
#include <vector>

namespace jt {
namespace pathfinder {
class Node : public NodeInterface {
public:
    void addNeighbour(std::weak_ptr<NodeInterface> other) override;
    std::vector<std::weak_ptr<NodeInterface>> const& getNeighbours() const override;

    void visit() override;
    void unvisit() override;
    bool wasVisited() const override;

    jt::Vector2u const& getTilePosition() const override;

    void setPosition(jt::Vector2u pos);

    float getValue() const override;
    void setValue(float value) override;

    void setBlocked(bool blocked) override;
    bool getBlocked() const override;

private:
    bool m_visited { false };
    float m_value { -1.0f };
    jt::Vector2u m_position;
    std::vector<std::weak_ptr<jt::pathfinder::NodeInterface>> m_neighbours;
    int m_isBlocked { false };
};
} // namespace pathfinder
} // namespace jt
#endif // JAMTEMPLATE_NODE_HPP
