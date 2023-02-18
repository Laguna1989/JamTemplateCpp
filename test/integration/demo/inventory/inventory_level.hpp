#ifndef JAMTEMPLATE_INVENTORY_LEVEL_HPP
#define JAMTEMPLATE_INVENTORY_LEVEL_HPP

#include "tilemap/tile_layer.hpp"
#include "tilemap/tileson_loader.hpp"
#include <box2dwrapper/box2d_object.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_object.hpp>
#include <memory>

class InventoryLevel : public jt::GameObject {
public:
    InventoryLevel(std::weak_ptr<jt::Box2DWorldInterface> world);

    void loadTileLayers(jt::tilemap::TilesonLoader& loader);
    void loadLevelCollisions(jt::tilemap::TilesonLoader& loader);

private:
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround;
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerOverlay;

    std::weak_ptr<jt::Box2DWorldInterface> m_world;
    std::vector<std::shared_ptr<jt::Box2DObject>> m_colliders {};

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // JAMTEMPLATE_INVENTORY_LEVEL_HPP
