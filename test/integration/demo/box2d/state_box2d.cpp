#include "state_box2d.hpp"
#include <box2d/PlatformPlayer.hpp>
#include <box2dwrapper/box2d_world_impl.hpp>
#include <conversions.hpp>
#include <game_interface.hpp>
#include <input/input_manager.hpp>
#include <lerp.hpp>
#include <random/random.hpp>
#include <state_select.hpp>
#include <tilemap/tileson_loader.hpp>
#include <tweens/tween_rotation.hpp>
#include <tweens/tween_scale.hpp>

StatePlatformer::StatePlatformer(std::string const& levelName) { m_levelName = levelName; }

void StatePlatformer::doInternalCreate()
{
    //    getGame()->gfx().camera().setZoom(4.0f);
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 400.0f });

    loadLevel();

    CreatePlayer();
    m_contactListener = std::make_shared<MyContactListener>();
    m_contactListener->setPlayer(m_player);
    m_world->setContactListener(m_contactListener);

    m_vignette = std::make_shared<jt::Vignette>(jt::Vector2f { 400.0f, 300.0f });
    add(m_vignette);
    setAutoDraw(false);
}

void StatePlatformer::loadLevel()
{
    m_level = std::make_shared<Level>("assets/test/integration/demo/" + m_levelName, m_world);
    add(m_level);
}

void StatePlatformer::doInternalUpdate(float const elapsed)
{
    if (!m_ending && !getGame()->stateManager().getTransition()->isInProgress()) {
        std::int32_t const velocityIterations = 20;
        std::int32_t const positionIterations = 20;
        m_world->step(elapsed, velocityIterations, positionIterations);

        updateObjects(elapsed);
        m_level->update(elapsed);

        m_level->checkIfPlayerIsInKillbox(m_player->getPosition(), [this]() { endGame(); });
        m_level->checkIfPlayerIsInExit(
            m_player->getPosition(), [this](std::string const& newLevelName) {
                if (!m_ending) {
                    m_ending = true;
                    getGame()->stateManager().switchState(
                        std::make_shared<StatePlatformer>(newLevelName));
                }
            });

        handleCameraScrolling(elapsed);
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {

        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StatePlatformer::endGame()
{
    if (!m_ending) {
        m_ending = true;
        getGame()->stateManager().switchState(std::make_shared<StatePlatformer>(m_levelName));
    }
}

void StatePlatformer::handleCameraScrolling(float const elapsed)
{
    // TODO add y scrolling if needed
    auto ps = m_player->getPosOnScreen();

    float const rightMargin = 150.0f;
    float const leftMargin = 10.0f;

    float const scrollSpeed = 60.0f;
    auto& cam = getGame()->gfx().camera();

    auto const screenWidth = 400.0f;
    if (ps.x < leftMargin) {
        cam.move(jt::Vector2f { -scrollSpeed * elapsed, 0.0f });
        if (ps.x < rightMargin / 2) {
            cam.move(jt::Vector2f { -scrollSpeed * elapsed, 0.0f });
        }
    } else if (ps.x > screenWidth - rightMargin) {
        cam.move(jt::Vector2f { scrollSpeed * elapsed, 0.0f });
        if (ps.x > screenWidth - rightMargin / 3 * 2) {
            cam.move(jt::Vector2f { scrollSpeed * elapsed, 0.0f });
        }
    }

    // clamp camera to level bounds
    auto offset = cam.getCamOffset();
    if (offset.x < 0) {
        offset.x = 0;
    }
    auto const levelWidth = m_level->getLevelSizeInPixel().x;
    auto const maxCamPosition = levelWidth - screenWidth;
    if (offset.x > maxCamPosition) {
        offset.x = maxCamPosition;
    }
    cam.setCamOffset(offset);
}

void StatePlatformer::doInternalDraw() const
{
    m_level->draw();
    m_player->draw();
    m_vignette->draw();
}

void StatePlatformer::CreatePlayer()
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(48, 32.0f);
    m_player = std::make_shared<Player>(m_world, &bodyDef);
    m_player->setPosition(m_level->getPlayerStart());
    add(m_player);
}

std::string StatePlatformer::getName() const { return "Box2D"; }
