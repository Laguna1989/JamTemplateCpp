#ifndef GUARD_JAMTEMPLATE_TILE_HPP
#define GUARD_JAMTEMPLATE_TILE_HPP

#include "game_object.hpp"
#include "pathfinder/node_interface.hpp"
#include "shape.hpp"
#include "vector.hpp"
#include <memory>

namespace jt {
// TODO pass in INodeInterface as dependency via constructor injection
class Tile : public GameObject {
public:
    Tile(Vector2 pos, bool blocked);

    std::shared_ptr<jt::pathfinder::NodeInterface> getNode();
    jt::Vector2 getPosition();
    void setBlocked(bool blocked);
    bool getBlocked();
    void reset();

    void setColor(jt::Color const& c);

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    std::shared_ptr<jt::Shape> m_shape;
    std::shared_ptr<jt::pathfinder::NodeInterface> m_node;
    bool m_blocked { false };
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILE_HPP
