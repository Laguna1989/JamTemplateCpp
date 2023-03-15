#include "state_inventory.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <game_interface.hpp>
#include <inventory/character/character_controller_player.hpp>
#include <inventory/character/character_controller_walk.hpp>
#include <inventory/inventory_list_imgui.hpp>
#include <random/random.hpp>
#include <state_select.hpp>
#include <strutils.hpp>
#include <system_helper.hpp>
#include <tilemap/tileson_loader.hpp>
#include <Box2D/Box2D.h>

namespace {
void camFollowObject(jt::CamInterface& cam, jt::Vector2f const& windowSize,
    std::shared_ptr<jt::Box2DObject> obj, float elapsed)
{
    auto const objPos = obj->getPosition();
    auto const camPos = cam.getCamOffset();
    auto const dif = objPos - camPos;

    float const margin = 100.0f;
    float const moveSpeed = 90.0f;
    jt::Vector2f const screenSize = windowSize / cam.getZoom();
    if (dif.x < margin) {
        cam.move(jt::Vector2f { -moveSpeed, 0.0f } * elapsed);
        if (dif.x < margin * 0.5f) {
            cam.move(jt::Vector2f { -moveSpeed, 0.0f } * elapsed);
        }
    }

    if (dif.x > screenSize.x - margin) {
        cam.move(jt::Vector2f { moveSpeed, 0.0f } * elapsed);
        if (dif.x > screenSize.x - margin * 0.5f) {
            cam.move(jt::Vector2f { moveSpeed, 0.0f } * elapsed);
        }
    }

    if (dif.y < margin) {
        cam.move(jt::Vector2f { 0.0f, -moveSpeed } * elapsed);
        if (dif.y < margin * 0.5f) {
            cam.move(jt::Vector2f { 0.0f, -moveSpeed } * elapsed);
        }
    }

    if (dif.y > screenSize.y - margin) {
        cam.move(jt::Vector2f { 0.0f, moveSpeed } * elapsed);
        if (dif.y > screenSize.y - margin * 0.5f) {
            cam.move(jt::Vector2f { 0.0f, moveSpeed } * elapsed);
        }
    }
}
} // namespace

void StateInventory::onCreate()
{
    // -2: tiles background
    getGame()->gfx().createZLayer(-2);
    // -1: tiles overlay
    getGame()->gfx().createZLayer(-1);

    getGame()->gfx().createZLayer(1);
    // 2: characters
    getGame()->gfx().createZLayer(2);
    getGame()->gfx().createZLayer(3);
    // 4: items
    getGame()->gfx().createZLayer(4);
    // 5: hud
    getGame()->gfx().createZLayer(5);
    m_clock = std::make_shared<WorldClock>();
    add(m_clock);

    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });
    createItemRepository();

    loadTilemap();

    createWorldItems();

    createObjects();
    m_player = std::make_shared<Character>(m_world, m_itemRepository,
        std::make_unique<CharacterControllerPlayer>(getGame()->input().keyboard()),
        m_player_start_pos, true);
    add(m_player);

    m_characters.push_back(m_player);
    auto guy = std::make_shared<Character>(m_world, m_itemRepository,
        std::make_unique<CharacterControllerWalk>(), jt::Vector2f { 13 * 24, 4 * 24 });
    add(guy);
    m_characters.push_back(guy);

    setAutoDraw(false);

    m_pickupSound = getGame()->audio().addTemporarySound("assets/test/integration/demo/test.ogg");
}

void StateInventory::onEnter() { }

void StateInventory::createObjects()
{
    std::cout << "create world objects\n";
    m_level->createDoors(m_temperatureManager, m_world);
    m_player_start_pos = m_level->getPlayerStartingPos();
    for (auto const& obj : m_level->getObjects()) {
        auto const type = obj.properties.strings.at("type");
        if (type == "controller") {
            auto controller = std::make_shared<ObjectController>(obj.position);
            if (obj.properties.strings.count("doors") == 1) {
                auto const allDoorsString = obj.properties.strings.at("doors");
                auto allDoorsVector = strutil::split(allDoorsString, ",");
                for (auto& doorString : allDoorsVector) {
                    strutil::trim(doorString);
                    for (auto const& d : m_level->getDoors()) {
                        if (d->getDoorName() == doorString) {
                            controller->addDoor(d);
                        }
                    }
                }
            }
            if (obj.properties.strings.count("heaters") == 1) {
                auto const allHeatersString = obj.properties.strings.at("heaters");
                auto allHeaterssVector = strutil::split(allHeatersString, ",");
                for (auto& heaterString : allHeaterssVector) {
                    strutil::trim(heaterString);

                    auto const h = m_temperatureManager->getControllerByName(heaterString);
                    if (!jt::SystemHelper::is_uninitialized_weak_ptr(h)) {
                        controller->addHeater(h);
                    }
                }
            }

            add(controller);
            m_controllers.push_back(controller);
        }
    }
}

void StateInventory::createWorldItems()
{
    m_worldItems = std::make_shared<jt::ObjectGroup<WorldItem>>();
    std::cout << "createWorldItems\n";

    for (auto const& it : m_level->getItemObjects()) {
        if (it.type != "item") {
            //        continue; // once tileson supports the class attribute.
        }
        auto const refId = it.properties.strings.at("referenceid");
        spawnWorldItem(refId, it.position);
    }
    add(m_worldItems);
}

void StateInventory::loadTilemap()
{
    jt::tilemap::TilesonLoader loader { getGame()->cache().getTilemapCache(),
        "assets/test/integration/demo/spaceship_items.json" };

    m_level = std::make_shared<InventoryLevel>(m_world);
    add(m_level);
    m_level->loadTileLayers(loader);
    m_level->loadLevelCollisions(loader);

    loadTemperatureManager(loader);
}

void StateInventory::loadTemperatureManager(jt::tilemap::TilesonLoader& loader)
{
    m_temperatureManager = std::make_shared<TemperatureManager>(
        loader.loadNodesFromLayer("ground"), loader.loadObjectsFromLayer("temp"));

    add(m_temperatureManager);
}

void StateInventory::createItemRepository()
{
    m_itemRepository = std::make_shared<ItemRepository>();

    m_itemRepository->loadFromJson("assets/test/integration/demo/test_items.json");
}

void StateInventory::onUpdate(float elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }

    m_world->step(elapsed, 20, 20);

    camFollowObject(getGame()->gfx().camera(), getGame()->gfx().window().getSize(),
        m_player->getBox2DObject(), elapsed);

    handleCharacterTemperature();
    pickupItems();
    for (auto& c : m_controllers) {
        c->setPlayerPosition(m_player->getBox2DObject()->getPosition());
    }

    std::string const& itemToSpawn = m_player->getInventory()->getAndResetItemToSpawn();
    if (itemToSpawn != "") {
        auto const px = jt::Random::getInt(2, 8);
        auto const py = jt::Random::getInt(2, 8);
        jt::Vector2f const pos { px * 24.0f, py * 24.0f };
        spawnWorldItem(itemToSpawn, pos);
    }
}
void StateInventory::handleCharacterTemperature()
{
    for (auto c : m_characters) {
        auto const posFloat = c->getBox2DObject()->getPosition();
        jt::Vector2u const posInTiles { static_cast<unsigned int>(posFloat.x / 24),
            static_cast<unsigned int>(posFloat.y / 24) };
        auto node = m_temperatureManager->getNodeAt(posInTiles);
        if (node) {
            c->setCurrentTemperature(node->getCurrentTemperature());
        } else {
            c->setCurrentTemperature(0.0f);
        }
    }
}

void StateInventory::spawnWorldItem(std::string const& itemReferenceId, jt::Vector2f const& pos)
{
    auto item = m_itemRepository->createWorldItem(
        m_itemRepository->getItemReferenceFromString(itemReferenceId), textureManager());
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

                m_pickupSound->play();

                item.lock()->kill();
            }
        }
    }
}

void StateInventory::onDraw() const { drawObjects(); }
