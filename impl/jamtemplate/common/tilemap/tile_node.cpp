#include "tile_node.hpp"

jt::tilemap::TileNode::TileNode(std::shared_ptr<jt::DrawableInterface> drawable,
    std::shared_ptr<jt::pathfinder::NodeInterface> node)
    : m_node { node }
    , m_drawable { drawable }
{
    reset();
}

std::shared_ptr<jt::pathfinder::NodeInterface>& jt::tilemap::TileNode::getNode() { return m_node; }
std::shared_ptr<jt::DrawableInterface>& jt::tilemap::TileNode::getDrawable() { return m_drawable; }

void jt::tilemap::TileNode::setBlocked(bool blocked) { m_node->setBlocked(blocked); }
bool jt::tilemap::TileNode::getBlocked() const { return m_node->getBlocked(); }

void jt::tilemap::TileNode::reset()
{
    if (m_node) {
        m_node->setValue(-1);
        m_node->unvisit();
    }
}
