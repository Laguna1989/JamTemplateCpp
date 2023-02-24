
#include "inventory_level.hpp"

InventoryLevel::InventoryLevel(std::weak_ptr<jt::Box2DWorldInterface> world)
    : m_world { world }
{
}

void InventoryLevel::doCreate() { }
void InventoryLevel::doUpdate(float const elapsed)
{
    m_tileLayerGround->update(elapsed);
    m_tileLayerOverlay->update(elapsed);
    for (auto& door : m_doors) {
        door->update(elapsed);
    }
}
void InventoryLevel::doDraw() const
{
    m_tileLayerGround->draw(renderTarget());
    for (auto& door : m_doors) {
        door->draw();
    }
    m_tileLayerOverlay->draw(renderTarget());
}

void InventoryLevel::loadLevelCollisions(jt::tilemap::TilesonLoader& loader)
{
    auto tileCollisions = loader.loadCollisionsFromLayer("ground");

    tileCollisions.refineColliders(24);
    for (auto const& r : tileCollisions.getRects()) {
        b2BodyDef bodyDef;
        bodyDef.fixedRotation = true;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(r.left + r.width / 2.0f, r.top + r.height / 2.0f);

        b2FixtureDef fixtureDef;
        b2PolygonShape boxCollider {};
        boxCollider.SetAsBox(r.width / 2.0f, r.height / 2.0f);
        fixtureDef.shape = &boxCollider;

        auto collider = std::make_shared<jt::Box2DObject>(m_world.lock(), &bodyDef);
        collider->getB2Body()->CreateFixture(&fixtureDef);

        m_colliders.push_back(collider);
    }
}
void InventoryLevel::loadTileLayers(jt::tilemap::TilesonLoader& loader)
{
    m_tileLayerGround = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("ground", textureManager(), "assets/test/integration/demo/"));
    m_tileLayerGround->setScreenSizeHint(jt::Vector2f { 400, 300 });
    m_tileLayerGround->setZ(-2);

    m_tileLayerOverlay = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("overlay", textureManager(), "assets/test/integration/demo/"));
    m_tileLayerOverlay->setScreenSizeHint(jt::Vector2f { 400, 300 });
    m_tileLayerOverlay->setZ(-1);

    // TODO move following code into separate functions
    m_itemsLayer = std::make_shared<jt::tilemap::ObjectLayer>(loader.loadObjectsFromLayer("items"));
    m_invObjectsLayer
        = std::make_shared<jt::tilemap::ObjectLayer>(loader.loadObjectsFromLayer("objects"));
}

std::vector<jt::tilemap::InfoRect> InventoryLevel::getItemObjects()
{
    return m_itemsLayer->getObjects();
}

std::vector<jt::tilemap::InfoRect> InventoryLevel::getObjects()
{
    return m_invObjectsLayer->getObjects();
}

std::vector<std::shared_ptr<ObjectDoor>> InventoryLevel::getDoors() { return m_doors; }

void InventoryLevel::createDoors(std::shared_ptr<TemperatureManager>& temperatureManager,
    std::shared_ptr<jt::Box2DWorldInterface> world)
{
    for (auto const& obj : m_invObjectsLayer->getObjects()) {
        auto const type = obj.properties.strings.at("type");
        if (type == "door") {
            auto const node = temperatureManager->getNodeAt(
                jt::Vector2u { static_cast<unsigned int>(obj.position.x / 24),
                    static_cast<unsigned int>(obj.position.y / 24) });
            auto door = std::make_shared<ObjectDoor>(node, world);
            door->setDoorName(obj.name);
            door->m_closed = !obj.properties.bools.at("initial_open");
            door->m_inflowOpen = obj.properties.floats.at("temp_inflow_open");
            door->m_inflowClosed = obj.properties.floats.at("temp_inflow_closed");
            door->setGameInstance(getGame());
            door->create();
            m_doors.push_back(door);
        }
    }
}
jt::Vector2f InventoryLevel::getPlayerStartingPos() const
{
    for (auto const& obj : m_invObjectsLayer->getObjects()) {
        auto const type = obj.properties.strings.at("type");
        if (type == "player_start") {
            return obj.position;
        }
    }
    return jt::Vector2f {};
}
