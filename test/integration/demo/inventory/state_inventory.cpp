#include "state_inventory.hpp"
#include "../state_select.hpp"
#include "box2dwrapper/box2d_world_impl.hpp"
#include "game_interface.hpp"
#include "inventory_list_imgui.hpp"
#include "random/random.hpp"
#include "tilemap/tileson_loader.hpp"

namespace {
void camFollowObject(jt::CamInterface& cam, jt::Vector2f const& windowSize,
    std::shared_ptr<jt::Box2DObject> obj, float elapsed)
{
    auto const objPos = obj->getPosition();
    auto const camPos = cam.getCamOffset();
    auto const dif = objPos - camPos;

    float const margin = 80.0f;
    float const moveSpeed = 60.0f;
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

void StateInventory::doInternalCreate()
{
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });

    createItemRepository();

    loadTilemap();

    createWorldItems();

    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(5 * 24, 7 * 24);
    m_player = std::make_shared<PlayerCharacter>(m_world, &bodyDef, m_itemRepository);
    add(m_player);

    setAutoDraw(false);

    m_pickupSound = std::make_shared<jt::Sound>("assets/test.ogg");
    getGame()->audio().addTemporarySound(m_pickupSound);
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

    auto tileCollisions = loader.loadCollisionsFromLayer("ground");
    tileCollisions.refineColliders();
    for (auto const& r : tileCollisions.getRects()) {
        b2BodyDef bodyDef;
        bodyDef.fixedRotation = true;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(r.left + r.width / 2.0f, r.top + r.height / 2.0f);

        b2FixtureDef fixtureDef;
        b2PolygonShape boxCollider {};
        boxCollider.SetAsBox(r.width / 2.0f, r.height / 2.0f);
        fixtureDef.shape = &boxCollider;

        auto collider = std::make_shared<jt::Box2DObject>(m_world, &bodyDef);
        collider->getB2Body()->CreateFixture(&fixtureDef);

        m_colliders.push_back(collider);
    }
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

    m_world->step(elapsed, 20, 20);

    camFollowObject(
        getGame()->gfx().camera(), getGame()->gfx().window().getSize(), m_player, elapsed);

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

                m_pickupSound->play();

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
