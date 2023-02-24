#ifndef JAMTEMPLATE_INVENTORY_LEVEL_HPP
#define JAMTEMPLATE_INVENTORY_LEVEL_HPP

#include <box2dwrapper/box2d_object.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_object.hpp>
#include <inventory/objects/object_door.hpp>
#include <inventory/temperature/temperature_manager.hpp>
#include <tilemap/object_layer.hpp>
#include <tilemap/tile_layer.hpp>
#include <tilemap/tileson_loader.hpp>
#include <memory>

class InventoryLevel : public jt::GameObject {
public:
    InventoryLevel(std::weak_ptr<jt::Box2DWorldInterface> world);

    void loadTileLayers(jt::tilemap::TilesonLoader& loader);
    void loadLevelCollisions(jt::tilemap::TilesonLoader& loader);

    std::vector<jt::tilemap::InfoRect> getItemObjects();

    // TODO remove/make private once everything is stored in this class
    std::vector<jt::tilemap::InfoRect> getObjects();

    // TODO make private when it can be called from inside this class
    void createDoors(std::shared_ptr<TemperatureManager>& temperatureManager,
        std::shared_ptr<jt::Box2DWorldInterface> world);

    std::vector<std::shared_ptr<ObjectDoor>> getDoors();

    jt::Vector2f getPlayerStartingPos() const;

private:
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround;
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerOverlay;

    std::shared_ptr<jt::tilemap::ObjectLayer> m_itemsLayer;

    std::weak_ptr<jt::Box2DWorldInterface> m_world;
    std::vector<std::shared_ptr<jt::Box2DObject>> m_colliders {};

    std::shared_ptr<jt::tilemap::ObjectLayer> m_invObjectsLayer { nullptr };
    // TODO find a more generic way to store Objects
    std::vector<std::shared_ptr<ObjectDoor>> m_doors {};

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // JAMTEMPLATE_INVENTORY_LEVEL_HPP
