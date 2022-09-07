#ifndef JAMTEMPLATE_LEVEL_HPP
#define JAMTEMPLATE_LEVEL_HPP

#include "box2dwrapper/box2d_object.hpp"
#include "tilemap/tile_layer.hpp"
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_object.hpp>

class Level : public jt::GameObject {
public:
    Level(std::string const& fileName, std::weak_ptr<jt::Box2DWorldInterface> world);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::string m_fileName { "" };
    std::weak_ptr<jt::Box2DWorldInterface> m_world;

    std::vector<std::shared_ptr<jt::Box2DObject>> m_colliders {};
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround { nullptr };
};

#endif // JAMTEMPLATE_LEVEL_HPP
