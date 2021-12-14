#ifndef GUARD_JAMTEMPLATE_TILENODE_HPP
#define GUARD_JAMTEMPLATE_TILENODE_HPP

#include "drawable_interface.hpp"
#include "pathfinder/node_interface.hpp"
#include "vector.hpp"
#include <memory>

namespace jt {
namespace tilemap {
class TileNode {
public:
    TileNode(std::shared_ptr<jt::DrawableInterface> drawable,
        std::shared_ptr<jt::pathfinder::NodeInterface> node, bool blocked);

    std::shared_ptr<jt::pathfinder::NodeInterface> getNode();
    std::shared_ptr<jt::DrawableInterface> getDrawable();

    void setBlocked(bool blocked);
    bool getBlocked();
    void reset();

private:
    std::shared_ptr<jt::DrawableInterface> m_drawable;
    std::shared_ptr<jt::pathfinder::NodeInterface> m_node;
    bool m_blocked { false };
};

} // namespace tilemap
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILENODE_HPP
