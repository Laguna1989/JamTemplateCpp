#include "state_box2d.hpp"
#include <box2d/movement_object.hpp>
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

void StateBox2d::doInternalCreate()
{
    //    getGame()->gfx().camera().setZoom(4.0f);
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 100.0f });

    loadLevel();

    CreatePlayer();
}

void StateBox2d::loadLevel()
{
    jt::tilemap::TilesonLoader loader { "assets/test/integration/demo/platformer.json" };

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

        auto collider = std::make_shared<jt::Box2DObject>(m_world, &bodyDef);
        collider->getB2Body()->CreateFixture(&fixtureDef);

        m_colliders.push_back(collider);
    }
}

void StateBox2d::doInternalUpdate(float const elapsed)
{
    int32 const velocityIterations = 6;
    int32 const positionIterations = 2;

    m_world->step(elapsed, velocityIterations, positionIterations);

    updateObjects(elapsed);
    m_tileLayerGround->update(elapsed);

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateBox2d::doInternalDraw() const { m_tileLayerGround->draw(renderTarget()); }

void StateBox2d::CreatePlayer()
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(48, 32.0f);
    m_player = std::make_shared<Player>(m_world, &bodyDef);

    add(m_player);
}

std::string StateBox2d::getName() const { return "Box2D"; }
