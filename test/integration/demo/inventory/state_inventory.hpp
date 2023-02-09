#ifndef JAMTEMPLATE_STATE_INVENTORY_HPP
#define JAMTEMPLATE_STATE_INVENTORY_HPP

#include "object_door.hpp"
#include "tilemap/tileson_loader.hpp"
#include <audio/sound.hpp>
#include <game_state.hpp>
#include <inventory/character/character.hpp>
#include <inventory/character_sheet_imgui.hpp>
#include <inventory/inventory_interface.hpp>
#include <inventory/item_repository.hpp>
#include <inventory/temperature_manager.hpp>
#include <object_group.hpp>
#include <tilemap/object_layer.hpp>
#include <tilemap/tile_layer.hpp>

class StateInventory : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround;
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerOverlay;
    std::shared_ptr<jt::tilemap::ObjectLayer> m_itemsLayer;
    std::shared_ptr<jt::tilemap::ObjectLayer> m_objectsLayer;

    std::shared_ptr<Character> m_player;
    std::vector<std::shared_ptr<Character>> m_characters;

    std::shared_ptr<ItemRepository> m_itemRepository;
    std::shared_ptr<jt::ObjectGroup<WorldItem>> m_worldItems;

    std::shared_ptr<jt::SoundInterface> m_pickupSound;

    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };
    std::vector<std::shared_ptr<jt::Box2DObject>> m_colliders {};

    std::shared_ptr<TemperatureManager> m_temperatureManager { nullptr };
    // TODO find a more generic way to store those
    std::vector<std::shared_ptr<ObjectDoor>> m_doors;

    void createItemRepository();
    void loadTilemap();
    void createWorldItems();
    void pickupItems();
    void spawnWorldItem(std::string const& itemReferenceId, jt::Vector2f const& pos);
    void loadTemperatureManager(jt::tilemap::TilesonLoader& loader);
    void handleCharacterTemperature();
};

#endif // JAMTEMPLATE_STATE_INVENTORY_HPP
