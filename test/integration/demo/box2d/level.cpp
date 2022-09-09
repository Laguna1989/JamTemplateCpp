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
    m_background = std::make_shared<jt::Shape>();
    m_background->makeRect(jt::Vector2f { 400, 300 }, textureManager());

    m_background->setCamMovementFactor(0.0f);

    jt::tilemap::TilesonLoader loader { m_fileName };

    loadLevelSettings(loader);
    loadLevelTileLayer(loader);
    loadLevelCollisions(loader);

    loadLevelKillboxes(loader);
}

void Level::loadLevelKillboxes(jt::tilemap::TilesonLoader& loader)
{
    m_killboxes = loader.loadObjectsFromLayer("killboxes");
}

void Level::loadLevelCollisions(jt::tilemap::TilesonLoader& loader)
{
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

void Level::loadLevelTileLayer(jt::tilemap::TilesonLoader& loader)
{
    m_tileLayerGround = std::make_shared<jt::tilemap::TileLayer>(
        loader.loadTilesFromLayer("ground", textureManager(), "assets/test/integration/demo/"));
}

void Level::loadLevelSettings(jt::tilemap::TilesonLoader& loader)
{
    auto settings = loader.loadObjectsFromLayer("settings");
    for (auto const& info : settings) {
        if (info.name == "map_settings") {
            auto const props = settings.front().properties;
            m_background->setColor(jt::Color { static_cast<uint8_t>(props.ints.at("bg_r")),
                static_cast<uint8_t>(props.ints.at("bg_g")),
                static_cast<uint8_t>(props.ints.at("bg_b")) });
        } else if (info.name == "player_start") {
            m_playerStart = info.position;
        }
    }
}
void Level::doUpdate(float const elapsed)
{
    m_background->update(elapsed);
    m_tileLayerGround->update(elapsed);
}

void Level::doDraw() const
{
    m_background->draw(renderTarget());
    m_tileLayerGround->draw(renderTarget());
}
jt::Vector2f Level::getPlayerStart() const { return m_playerStart; }

bool Level::checkIfPlayerIsInKillbox(jt::Vector2f const& playerPosition) const
{
    if (m_killboxes.empty()) {
        return false;
    }
    for (auto const& kb : m_killboxes) {

        bool const overlapsX
            = playerPosition.x > kb.position.x && playerPosition.x < kb.position.x + kb.size.x;
        bool const overlapsY
            = playerPosition.y > kb.position.y && playerPosition.y < kb.position.y + kb.size.y;
        if (overlapsX && overlapsY) {
            return true;
        }
    }
    return false;
}
