#ifndef GUARD_JAMTEMPLATE_TILE_HPP
#define GUARD_JAMTEMPLATE_TILE_HPP

#include "drawable_interface.hpp"
#include "game_object.hpp"
#include "pathfinder/node_interface.hpp"
#include "vector.hpp"
#include <memory>

namespace jt {
// TODO pass in INodeInterface and drawable as dependencies via constructor injection
class Tile : public GameObject {
public:
    Tile(std::shared_ptr<jt::DrawableInterface> drawable,
        std::shared_ptr<jt::pathfinder::NodeInterface> node, bool blocked);

    std::shared_ptr<jt::pathfinder::NodeInterface> getNode();
    std::shared_ptr<jt::DrawableInterface> getDrawable();
    jt::Vector2 getPosition();
    void setBlocked(bool blocked);
    bool getBlocked();
    void reset();

    void setColor(jt::Color const& c);

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    std::shared_ptr<jt::DrawableInterface> m_drawable;
    std::shared_ptr<jt::pathfinder::NodeInterface> m_node;
    bool m_blocked { false };
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILE_HPP
