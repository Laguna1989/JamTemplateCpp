#ifndef GUARD_JAMTEMPLATE_NODE_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_NODE_INTERFACE_HPP

#include "vector.hpp"
#include <memory>
#include <vector>

namespace jt {
namespace pathfinder {
class NodeInterface {
public:
    virtual ~NodeInterface() = default;
    virtual std::vector<std::weak_ptr<NodeInterface>> getNeighbours() = 0;
    virtual void visit() = 0;
    virtual void unvisit() = 0;
    virtual bool wasVisited() = 0;
    virtual void addNeighbour(std::weak_ptr<NodeInterface> other) = 0;
    virtual jt::Vector2u getTilePosition() const = 0;
    virtual float getValue() = 0;
    virtual void setValue(float value) = 0;
};

} // namespace pathfinder
} // namespace jt
#endif // GUARD_JAMTEMPLATE_NODE_INTERFACE_HPP
