#include "tile.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "pathfinder/node.hpp"

namespace jt {
Tile::Tile(jt::Vector2 pos, bool blocked)
{
    auto node = std::make_shared<jt::pathfinder::Node>();
    node->setPosition(pos);
    m_node = node;
    m_blocked = blocked;
}
void Tile::doCreate()
{
    m_shape = jt::dh::createShapeRect({ 19, 19 });
    if (m_blocked) {
        m_shape->setColor(jt::colors::Black);
    }
}
void Tile::doUpdate(float const elapsed)
{
    m_shape->setPosition(getPosition() * 20.0f);
    m_shape->update(elapsed);
}
void Tile::doDraw() const { m_shape->draw(getGame()->getRenderTarget()); }

std::shared_ptr<jt::pathfinder::NodeInterface> Tile::getNode() { return m_node; }

jt::Vector2 Tile::getPosition() { return m_node->getPosition(); }
void Tile::setBlocked(bool blocked) { m_blocked = blocked; }
bool Tile::getBlocked() { return m_blocked; }
void Tile::setColor(jt::Color const& c) { m_shape->setColor(c); }
void Tile::reset()
{
    m_node->setValue(-1);
    m_node->unvisit();
    setColor(jt::colors::White);
    if (m_blocked) {
        m_shape->setColor(jt::colors::Black);
    }
}
} // namespace jt
