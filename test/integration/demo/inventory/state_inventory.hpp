#ifndef JAMTEMPLATE_STATE_INVENTORY_HPP
#define JAMTEMPLATE_STATE_INVENTORY_HPP

#include <audio/sound/sound.hpp>
#include <game_state.hpp>
#include <inventory/character/character.hpp>
#include <inventory/character_sheet_imgui.hpp>
#include <inventory/inventory_interface.hpp>
#include <inventory/inventory_level.hpp>
#include <inventory/item_repository.hpp>
#include <inventory/objects/object_controller.hpp>
#include <inventory/objects/object_door.hpp>
#include <inventory/temperature/temperature_manager.hpp>
#include <inventory/world_clock.hpp>
#include <object_group.hpp>
#include <tilemap/object_layer.hpp>
#include <tilemap/tile_layer.hpp>
#include <tilemap/tileson_loader.hpp>

class StateInventory : public jt::GameState {
public:
    void onCreate() override;

private:
    void onEnter() override;

public:
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };

    std::shared_ptr<Character> m_player;
    std::vector<std::shared_ptr<Character>> m_characters;

    std::shared_ptr<ItemRepository> m_itemRepository;
    std::shared_ptr<jt::ObjectGroup<WorldItem>> m_worldItems;

    std::shared_ptr<jt::SoundInterface> m_pickupSound;

    std::shared_ptr<InventoryLevel> m_level { nullptr };

    std::shared_ptr<TemperatureManager> m_temperatureManager { nullptr };
    // TODO find a more generic way to store Objects
    std::vector<std::shared_ptr<ObjectController>> m_controllers {};

    std::shared_ptr<WorldClock> m_clock { nullptr };

    void createItemRepository();
    void loadTilemap();
    void createWorldItems();
    void pickupItems();
    void spawnWorldItem(std::string const& itemReferenceId, jt::Vector2f const& pos);
    void loadTemperatureManager(jt::tilemap::TilesonLoader& loader);
    void handleCharacterTemperature();
    jt::Vector2f m_player_start_pos;
    void createObjects();
};

#endif // JAMTEMPLATE_STATE_INVENTORY_HPP
