#include "level.hpp"
#include <box2d/enemy_movement_horizontal.hpp>
#include <game_interface.hpp>
#include <math_helper.hpp>
#include <strutils.hpp>
#include <tilemap/tileson_loader.hpp>
#include <Box2D/Box2D.h>

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

    jt::tilemap::TilesonLoader loader { getGame()->cache().getTilemapCache(), m_fileName };

    loadLevelSize(loader);
    loadLevelSettings(loader);
    loadLevelTileLayer(loader);
    loadLevelCollisions(loader);
    loadLevelKillboxes(loader);
    loadMovingPlatforms(loader);

    auto const enemies = loader.loadObjectsFromLayer("enemies");
    for (auto const& enemy : enemies) {
        if (enemy.name == "bee") {
            std::shared_ptr<EnemyMovementInterface> movement { nullptr };
            if (enemy.properties.strings.at("movement") == "horizontal") {
                movement = std::make_shared<EnemyMovementHorizontal>(enemy.position.x,
                    enemy.position.x + enemy.properties.ints.at("distance_in_tiles") * 8.0f);
            }
            auto bee = std::make_shared<Bee>(m_world.lock(), enemy.position, movement);
            bee->setGameInstance(getGame());
            bee->create();
            m_bees.push_back(bee);
        }
    }
}

void Level::loadMovingPlatforms(jt::tilemap::TilesonLoader& loader)
{
    auto const platform_infos = loader.loadObjectsFromLayer("platforms");
    std::map<std::string, jt::Vector2f> allPositionsInLevel;
    for (auto const& p : platform_infos) {
        if (p.properties.strings.empty()) {
            allPositionsInLevel[p.name] = p.position;
        }
    }
    for (auto const& p : platform_infos) {
        if (!p.properties.strings.empty()) {
            std::vector<jt::Vector2f> currentPlatformPositions;
            auto const positionsString = p.properties.strings.at("positions");
            auto const individualPositionStrings = strutil::split(positionsString, ",");
            for (auto const& ps : individualPositionStrings) {
                if (allPositionsInLevel.count(ps) == 0) {
                    getGame()->logger().warning("position not found in level: " + ps, { "level" });
                }
                currentPlatformPositions.push_back(allPositionsInLevel[ps]);
            }
            float timeoffset = 0.0f;
            if (p.properties.floats.count("timeoffset") == 1) {
                timeoffset = p.properties.floats.at("timeoffset");
            }
            auto platform = std::make_shared<MovingPlatform>(m_world.lock(), p.size,
                currentPlatformPositions, p.properties.floats.at("velocity"), timeoffset);
            platform->setGameInstance(getGame());
            platform->create();
            m_movingPlatforms.push_back(platform);
        }
    }
}

void Level::loadLevelSize(jt::tilemap::TilesonLoader const& loader)
{
    auto const sizeInTiles = loader.getMapSizeInTiles();
    m_levelSizeInPixel = jt::Vector2f { 8.0f * sizeInTiles.x, 8.0f * sizeInTiles.y };
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
            m_background->setColor(
                jt::Color { static_cast<uint8_t>(info.properties.ints.at("bg_r")),
                    static_cast<uint8_t>(info.properties.ints.at("bg_g")),
                    static_cast<uint8_t>(info.properties.ints.at("bg_b")) });
        } else if (info.name == "player_start") {
            m_playerStart = info.position;
        } else if (info.name == "exit") {
            auto exit = Exit { info };
            exit.setGameInstance(getGame());
            exit.create();
            m_exits.emplace_back(exit);
        }
    }
}

void Level::doUpdate(float const elapsed)
{
    m_background->update(elapsed);
    m_tileLayerGround->update(elapsed);
    for (auto& exit : m_exits) {
        exit.update(elapsed);
    }
    for (auto& p : m_movingPlatforms) {
        p->update(elapsed);
    }
    for (auto& b : m_bees) {
        b->update(elapsed);
    }
}

void Level::doDraw() const
{
    m_background->draw(renderTarget());
    m_tileLayerGround->draw(renderTarget());
    for (auto const& exit : m_exits) {
        exit.draw();
    }
    for (auto const& p : m_movingPlatforms) {
        p->draw();
    }
    for (auto const& b : m_bees) {
        b->draw();
    }
}

jt::Vector2f Level::getPlayerStart() const { return m_playerStart; }

void Level::checkIfPlayerIsInKillbox(
    jt::Vector2f const& playerPosition, std::function<void(void)> callback) const
{
    // TODO move check to separate Killbox class
    for (auto const& kb : m_killboxes) {
        jt::Rectf const killboxRect { kb.position.x, kb.position.y, kb.size.x, kb.size.y };
        if (jt::MathHelper::checkIsIn(killboxRect, playerPosition)) {
            callback();
            break;
        }
    }
}

void Level::checkIfPlayerIsInExit(
    jt::Vector2f const& playerPosition, std::function<void(std::string const&)> callback)
{
    for (auto& exit : m_exits) {
        exit.checkIfPlayerIsInExit(playerPosition, callback);
        break;
    }
}

jt::Vector2f Level::getLevelSizeInPixel() const { return m_levelSizeInPixel; }
