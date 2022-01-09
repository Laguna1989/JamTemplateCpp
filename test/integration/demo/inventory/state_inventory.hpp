#ifndef GUARD_JAMTEMPLATE_STATE_INVENTORY_HPP
#define GUARD_JAMTEMPLATE_STATE_INVENTORY_HPP

#include "character.hpp"
#include "character_sheet_imgui.hpp"
#include "game_state.hpp"
#include "inventory_interface.hpp"
#include "item_repository.hpp"
#include "object_group.hpp"
#include "tilemap/object_layer.hpp"
#include "tilemap/tile_layer.hpp"

class StateInventory : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround;
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerOverlay;
    std::shared_ptr<jt::tilemap::ObjectLayer> m_objectsLayer;

    std::shared_ptr<PlayerCharacter> m_player;

    std::shared_ptr<ItemRepository> m_itemRepository;
    std::shared_ptr<jt::ObjectGroup<WorldItem>> m_worldItems;
    void createItemRepository();
    void loadTilemap();
    void createWorldItems();
    void pickupItems();
    void spawnWorldItem(std::string const& itemReferenceId, jt::Vector2f const& pos);
};

#endif // GUARD_JAMTEMPLATE_STATE_INVENTORY_HPP
