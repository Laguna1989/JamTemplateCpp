
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
}
void InventoryLevel::doDraw() const
{
    m_tileLayerGround->draw(renderTarget());
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
    m_tileLayerGround->setZ(-1);
}
