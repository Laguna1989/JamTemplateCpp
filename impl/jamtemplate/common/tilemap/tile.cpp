#include "tile.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "pathfinder/node.hpp"

namespace jt {

Tile::Tile(std::shared_ptr<jt::DrawableInterface> drawable,
    std::shared_ptr<jt::pathfinder::NodeInterface> node, bool blocked)
{
    m_node = node;
    m_drawable = drawable;
    m_blocked = blocked;
    reset();
}

void Tile::doCreate() { }
void Tile::doUpdate(float const elapsed) { m_drawable->update(elapsed); }
void Tile::doDraw() const { m_drawable->draw(getGame()->getRenderTarget()); }

std::shared_ptr<jt::pathfinder::NodeInterface> Tile::getNode() { return m_node; }

jt::Vector2 Tile::getPosition() { return m_node->getPosition(); }
void Tile::setBlocked(bool blocked) { m_blocked = blocked; }
bool Tile::getBlocked() { return m_blocked; }
void Tile::setColor(jt::Color const& c) { m_drawable->setColor(c); }
void Tile::reset()
{
    m_node->setValue(-1);
    m_node->unvisit();
}
std::shared_ptr<jt::DrawableInterface> Tile::getDrawable() { return m_drawable; }

} // namespace jt
