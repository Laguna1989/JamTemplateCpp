#include "node.hpp"
#include <stdexcept>

std::vector<std::weak_ptr<jt::pathfinder::NodeInterface>> const&
jt::pathfinder::Node::getNeighbours()
{
    return m_neighbours;
}

void jt::pathfinder::Node::visit() { m_visited = true; }
void jt::pathfinder::Node::unvisit() { m_visited = false; }
bool jt::pathfinder::Node::wasVisited() { return m_visited; }

jt::Vector2u const& jt::pathfinder::Node::getTilePosition() const { return m_position; }

void jt::pathfinder::Node::setPosition(jt::Vector2u pos) { m_position = pos; }

void jt::pathfinder::Node::addNeighbour(std::weak_ptr<jt::pathfinder::NodeInterface> other)
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

float jt::pathfinder::Node::getValue() { return m_value; }

void jt::pathfinder::Node::setValue(float value) { m_value = value; }
int jt::pathfinder::Node::getTileID() { return 0; }

void jt::pathfinder::Node::setTileID(int id) { m_tileId = id; }
bool jt::pathfinder::Node::getBlocked() { return m_isBlocked; }
void jt::pathfinder::Node::setBlocked(bool blocked) { m_isBlocked = blocked; }
