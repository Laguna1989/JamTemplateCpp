#include "state_inventory.hpp"
#include "../control_command_move_cam.hpp"
#include "../state_select.hpp"
#include "game_interface.hpp"
#include "inventory_list_imgui.hpp"
#include "random/random.hpp"
#include "tilemap/tileson_loader.hpp"

void StateInventory::doInternalCreate()
{
    createItemRepository();

    loadTilemap();

    createWorldItems();

    m_player = std::make_shared<PlayerCharacter>(m_itemRepository);
    add(m_player);

    setAutoDraw(false);

    float const scrollSpeed = 170.0f;
    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::W, jt::KeyCode::Up },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { 0.0f, -scrollSpeed }, getGame()->gfx().camera()));

    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::A, jt::KeyCode::Left },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { -scrollSpeed, 0.0f }, getGame()->gfx().camera()));

    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::S, jt::KeyCode::Down },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { 0.0f, scrollSpeed }, getGame()->gfx().camera()));

    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::D, jt::KeyCode::Right },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { scrollSpeed, 0.0f }, getGame()->gfx().camera()));
}

void StateInventory::createWorldItems()
{
    m_worldItems = std::make_shared<jt::ObjectGroup<WorldItem>>();

    for (auto it : m_objectsLayer->getObjects()) {
        if (it.type == "item") {
            auto const refId = it.properties.strings.at("referenceid");
            spawnWorldItem(refId, it.position);
        }
    }
    add(m_worldItems);
}

void StateInventory::loadTilemap()
{
    jt::tilemap::TilesonLoader loader { "assets/demos/inventory/spaceship_items.json" };

    m_tileLayerGround = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("ground", getGame()->gfx().textureManager()));
    m_tileLayerGround->setScreenSizeHint(jt::Vector2f { 400, 300 });

    m_tileLayerOverlay = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("overlay", getGame()->gfx().textureManager()));
    m_tileLayerOverlay->setScreenSizeHint(jt::Vector2f { 400, 300 });

    m_objectsLayer
        = std::make_shared<jt::tilemap::ObjectLayer>(loader.loadObjectsFromLayer("items"));
}

void StateInventory::createItemRepository()
{
    m_itemRepository = std::make_shared<ItemRepository>();

    m_itemRepository->loadFromJson("assets/demos/inventory/test_items.json");
}

void StateInventory::doInternalUpdate(float elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }

    m_tileLayerGround->update(elapsed);
    m_tileLayerOverlay->update(elapsed);

    pickupItems();

    std::string const& itemToSpawn = m_player->getInventory()->getAndResetItemToSpawn();
    if (itemToSpawn != "") {
        auto const px = jt::Random::getInt(2, 8);
        auto const py = jt::Random::getInt(2, 8);
        jt::Vector2f const pos { px * 24.0f, py * 24.0f };
        spawnWorldItem(itemToSpawn, pos);
    }
}

void StateInventory::spawnWorldItem(std::string const& itemReferenceId, jt::Vector2f const& pos)
{
    auto item = m_itemRepository->createWorldItem(
        m_itemRepository->getItemReferenceFromString(itemReferenceId),
        getGame()->gfx().textureManager());
    item->getDrawable()->setPosition(pos);
    add(item);
    m_worldItems->push_back(item);
}

void StateInventory::pickupItems()
{
    if (getGame()->input().mouse()->justPressed(jt::MouseButtonCode::MBLeft)) {
        auto const mp = getGame()->input().mouse()->getMousePositionWorld();
        for (auto& item : *m_worldItems) {
            auto const bounds = item.lock()->getDrawable()->getGlobalBounds();
            bool const overlapsX = mp.x > bounds.left && mp.x < bounds.left + bounds.width;
            bool const overlapsY = mp.y > bounds.top && mp.y < bounds.top + bounds.height;
            if (overlapsX && overlapsY) {
                m_player->getInventory()->addItem(item.lock()->getRefId());
                item.lock()->kill();
            }
        }
    }
}

void StateInventory::doInternalDraw() const
{
    m_tileLayerGround->draw(getGame()->gfx().target());

    m_tileLayerOverlay->draw(getGame()->gfx().target());
    drawObjects();
}
