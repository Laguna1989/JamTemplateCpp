#include "level.hpp"
#include "tilemap/tileson_loader.hpp"
#include "Box2D/Box2D.h"

Level::Level(std::string const& fileName, std::weak_ptr<jt::Box2DWorldInterface> world)
{
    m_fileName = fileName;
    m_world = world;
}

void Level::doCreate()
{
    jt::tilemap::TilesonLoader loader { m_fileName };

    m_tileLayerGround = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("ground", textureManager(), "assets/test/integration/demo/"));

    auto tileCollisions = loader.loadCollisionsFromLayer("ground");

    tileCollisions.refineColliders(8);
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
void Level::doUpdate(float const elapsed) { m_tileLayerGround->update(elapsed); }

void Level::doDraw() const { m_tileLayerGround->draw(renderTarget()); }
