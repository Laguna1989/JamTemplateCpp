#include "node.hpp"
#include <stdexcept>

namespace jt {
namespace pathfinder {

std::vector<std::weak_ptr<NodeInterface>> Node::getNeighbours() { return m_neighbours; }

void Node::visit() { m_visited = true; }

void Node::unvisit() { m_visited = false; }

bool Node::wasVisited() { return m_visited; }

jt::Vector2u Node::getTilePosition() const { return m_position; }

void Node::setPosition(jt::Vector2u pos) { m_position = pos; }

void Node::addNeighbour(std::weak_ptr<NodeInterface> other)
{
    auto o = other.lock();
    if (!o) {
        throw std::invalid_argument { "addNeighbour: Can not add nullptr." };
    }

    if (o.get() == this) {
        throw std::invalid_argument { "addNeighbour: Node can not have itself as neighbour." };
    }
    m_neighbours.push_back(other);
}

float Node::getValue() { return m_value; }

void Node::setValue(float value) { m_value = value; }

} // namespace pathfinder
} // namespace jt
