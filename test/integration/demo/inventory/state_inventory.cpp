#include "state_inventory.hpp"
#include "game_interface.hpp"
#include "random/random.hpp"
#include "tilemap/tileson_loader.hpp"

void StateInventory::doInternalCreate()
{

    createItemRepository();

    loadTilemap();

    createWorldItems();

    m_inventory = std::make_shared<ListInventory>(m_itemRepository);
    m_inventory->addItem("item_crystal_blue_01");
    m_inventory->addItem("item_crystal_blue_01");
    m_inventory->addItem("item_armor_armor_01");
    add(m_inventory);
    setAutoDraw(false);
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
        loader.loadTilesFromLayer("ground", getGame()->getTextureManager()));
    m_tileLayerGround->setScreenSizeHint(jt::Vector2f { 400, 300 });

    m_tileLayerOverlay = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("overlay", getGame()->getTextureManager()));
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
    m_tileLayerGround->update(elapsed);
    m_tileLayerOverlay->update(elapsed);

    pickupItems();

    std::string const& itemToSpawn = m_inventory->getAndResetItemToSpawn();
    if (itemToSpawn != "") {
        // TODO spwan around player and not at random position.
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
        getGame()->getTextureManager());
    item->getDrawable()->setPosition(pos);
    add(item);
    m_worldItems->push_back(item);
}
void StateInventory::pickupItems()
{
    if (getGame()->input()->mouse()->justPressed(jt::MouseButtonCode::MBLeft)) {
        auto const mp = getGame()->input()->mouse()->getMousePositionWorld();
        for (auto& item : *m_worldItems) {
            auto const bounds = item.lock()->getDrawable()->getGlobalBounds();
            bool const overlapsX = mp.x > bounds.left && mp.x < bounds.left + bounds.width;
            bool const overlapsY = mp.y > bounds.top && mp.y < bounds.top + bounds.height;
            if (overlapsX && overlapsY) {
                m_inventory->addItem(item.lock()->getRefId());
                item.lock()->kill();
            }
        }
    }
}

void StateInventory::doInternalDraw() const
{
    m_tileLayerGround->draw(getGame()->getRenderTarget());
    m_tileLayerOverlay->draw(getGame()->getRenderTarget());
    drawObjects();
}
