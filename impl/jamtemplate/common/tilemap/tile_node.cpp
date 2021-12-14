#include "tile_node.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "pathfinder/node.hpp"

namespace jt {
namespace tilemap {

TileNode::TileNode(std::shared_ptr<jt::DrawableInterface> drawable,
    std::shared_ptr<jt::pathfinder::NodeInterface> node, bool blocked)
{
    m_node = node;
    m_drawable = drawable;
    m_blocked = blocked;
    reset();
}

std::shared_ptr<jt::pathfinder::NodeInterface> TileNode::getNode() { return m_node; }

void TileNode::setBlocked(bool blocked) { m_blocked = blocked; }

bool TileNode::getBlocked() { return m_blocked; }

void TileNode::reset()
{
    if (m_node) {
        m_node->setValue(-1);
        m_node->unvisit();
    }
}

std::shared_ptr<jt::DrawableInterface> TileNode::getDrawable() { return m_drawable; }
} // namespace tilemap
} // namespace jt
