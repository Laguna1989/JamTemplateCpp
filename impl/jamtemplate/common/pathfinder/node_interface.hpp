#ifndef JAMTEMPLATE_NODE_INTERFACE_HPP
#define JAMTEMPLATE_NODE_INTERFACE_HPP

#include <vector.hpp>
#include <memory>
#include <vector>

namespace jt {
namespace pathfinder {
class NodeInterface {
public:
    /// get list of neighbour nodes
    /// \return vector of neighbour nodes
    virtual std::vector<std::weak_ptr<NodeInterface>> const& getNeighbours() const = 0;

    /// visit this node
    virtual void visit() = 0;

    /// unvisit this node
    virtual void unvisit() = 0;

    /// check if node was visited
    virtual bool wasVisited() const = 0;

    /// Add a neighbour.
    /// Node: One sided connection. Normally you want to connect A to B AND B to A.
    /// \param other neighbour node
    virtual void addNeighbour(std::weak_ptr<NodeInterface> other) = 0;

    /// get tile position (used for a*)
    /// \return position
    virtual jt::Vector2u const& getTilePosition() const = 0;

    /// get node value
    virtual float getValue() const = 0;

    /// set node value
    /// \param value value to be set
    virtual void setValue(float value) = 0;

    /// set tile blocked
    /// \param blocked true if blocked, false otherwise
    virtual void setBlocked(bool blocked) = 0;

    /// get tile blocked
    virtual bool getBlocked() const = 0;

    /// Destructor
    virtual ~NodeInterface() = default;

    // no copy, no move. Avoid slicing.
    NodeInterface(NodeInterface const&) = delete;
    NodeInterface(NodeInterface&&) = delete;
    NodeInterface& operator=(NodeInterface const&) = delete;
    NodeInterface& operator=(NodeInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    NodeInterface() = default;
};

} // namespace pathfinder
} // namespace jt
#endif // JAMTEMPLATE_NODE_INTERFACE_HPP
