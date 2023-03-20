
#ifndef JAMTEMPLATE_TILENODE_HPP
#define JAMTEMPLATE_TILENODE_HPP

#include <graphics/drawable_interface.hpp>
#include <pathfinder/node_interface.hpp>
#include <vector.hpp>
#include <memory>

namespace jt {
namespace tilemap {

class TileNode {
public:
    TileNode(std::shared_ptr<jt::DrawableInterface> drawable,
        std::shared_ptr<jt::pathfinder::NodeInterface> node);

    std::shared_ptr<jt::pathfinder::NodeInterface>& getNode();
    std::shared_ptr<jt::DrawableInterface>& getDrawable();

    void setBlocked(bool blocked);
    bool getBlocked() const;
    void reset();

private:
    std::shared_ptr<jt::pathfinder::NodeInterface> m_node;
    std::shared_ptr<jt::DrawableInterface> m_drawable;
};

} // namespace tilemap
} // namespace jt

#endif // JAMTEMPLATE_TILENODE_HPP
