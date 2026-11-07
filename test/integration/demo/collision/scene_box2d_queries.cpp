#include "scene_box2d_queries.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <conversions.hpp>
#include <drawable_helpers.hpp>
#include <math_helper.hpp>
#include <random/random.hpp>
#include <algorithm>
#include <array>
#include <optional>
#include <string>

namespace {
constexpr jt::Vector2f screenSize { 400.0f, 300.0f };
constexpr float wallThickness { 10.0f };
constexpr int numberOfInitialBodies { 20 };
constexpr std::size_t maxNumberOfBodies { 100u };
constexpr jt::Vector2f queryHalfSize { 30.0f, 30.0f };
constexpr float queryRotationSpeed { 90.0f }; // degrees per second
constexpr jt::Vector2f rayOrigin { 200.0f, 270.0f };
constexpr float rayLength { 600.0f };
constexpr jt::Color queryHitColor { 255, 255, 0 };
constexpr jt::Color rayHitColor { 0, 255, 255 };
} // namespace

void SceneBox2DQueries::doCreate()
{
    // no gravity, the bodies bounce around in a closed arena
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });

    float const halfThickness = wallThickness / 2.0f;
    createWall(jt::Vector2f { screenSize.x / 2.0f, -halfThickness },
        jt::Vector2f { screenSize.x / 2.0f, halfThickness });
    createWall(jt::Vector2f { screenSize.x / 2.0f, screenSize.y + halfThickness },
        jt::Vector2f { screenSize.x / 2.0f, halfThickness });
    createWall(jt::Vector2f { -halfThickness, screenSize.y / 2.0f },
        jt::Vector2f { halfThickness, screenSize.y / 2.0f });
    createWall(jt::Vector2f { screenSize.x + halfThickness, screenSize.y / 2.0f },
        jt::Vector2f { halfThickness, screenSize.y / 2.0f });

    for (auto i = 0; i != numberOfInitialBodies; ++i) {
        createBody(jt::Random::getRandomPointIn(jt::Rectf { 30.0f, 30.0f, 340.0f, 200.0f }));
    }

    m_queryShape = jt::dh::createShapeRect(
        queryHalfSize * 2.0f, jt::Color { 255, 255, 0, 50 }, textureManager());
    m_queryShape->setOrigin(jt::OriginMode::CENTER);

    m_rayLine = std::make_shared<jt::Line>();
    m_rayLine->setColor(rayHitColor);
    m_rayLine->setPosition(rayOrigin);

    m_rayHitMarker
        = jt::dh::createShapeRect(jt::Vector2f { 4.0f, 4.0f }, jt::colors::White, textureManager());
    m_rayHitMarker->setOrigin(jt::OriginMode::CENTER);

    m_info = jt::dh::createText(renderTarget(), "", 12);
    m_info->setTextAlign(jt::Text::TextAlign::LEFT);
    m_info->setPosition(jt::Vector2f { 4.0f, 282.0f });
    m_info->setShadow(jt::colors::Black, jt::Vector2f { 1.0f, 1.0f });
}

void SceneBox2DQueries::createWall(jt::Vector2f const& center, jt::Vector2f const& halfSize)
{
    auto bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    bodyDef.position = jt::Conversion::vec(center);
    auto wall = std::make_shared<jt::Box2DObject>(m_world, bodyDef);

    auto shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = 0.0f;
    auto const box = b2MakeBox(halfSize.x, halfSize.y);
    b2CreatePolygonShape(wall->getBodyId(), &shapeDef, &box);

    m_walls.push_back(wall);
}

void SceneBox2DQueries::createBody(jt::Vector2f const& position)
{
    auto const physicsBody = std::make_shared<PhysicsBody>(m_world, position);
    physicsBody->setGameInstance(getGame());
    physicsBody->create();
    m_bodies.push_back(physicsBody);
}

void SceneBox2DQueries::flashContacts()
{
    auto const events = m_world->getContactEvents();
    for (auto i = 0; i != events.beginCount; ++i) {
        auto const& event = events.beginEvents[i];
        for (auto const shapeId : { event.shapeIdA, event.shapeIdB }) {
            auto const physicsBody = PhysicsBody::fromShape(shapeId);
            if (physicsBody) {
                physicsBody->flash();
            }
        }
    }
}

void SceneBox2DQueries::queryQuad(jt::Vector2f const& center)
{
    m_queryHits.clear();

    // b2World_OverlapAABB only supports axis aligned boxes. A rotated quad needs a shape query,
    // which also tests the exact shape instead of only the bounding boxes.
    std::array const corners { b2Vec2 { -queryHalfSize.x, -queryHalfSize.y },
        b2Vec2 { queryHalfSize.x, -queryHalfSize.y }, b2Vec2 { queryHalfSize.x, queryHalfSize.y },
        b2Vec2 { -queryHalfSize.x, queryHalfSize.y } };
    auto const proxy = b2MakeOffsetProxy(corners.data(), static_cast<int>(corners.size()), 0.0f,
        jt::Conversion::vec(center), b2MakeRot(jt::MathHelper::deg2rad(m_queryRotation)));

    auto const callback = [](b2ShapeId shapeId, void* context) {
        auto const physicsBody = PhysicsBody::fromShape(shapeId);
        if (physicsBody) {
            static_cast<std::vector<PhysicsBody*>*>(context)->push_back(physicsBody);
        }
        // continue the query
        return true;
    };
    // the proxy points are already in world coordinates, so the query origin is zero
    b2World_OverlapShape(
        m_world->getWorldId(), b2Pos_zero, &proxy, b2DefaultQueryFilter(), callback, &m_queryHits);
}

void SceneBox2DQueries::castRay(jt::Vector2f const& target)
{
    auto direction = target - rayOrigin;
    if (jt::MathHelper::lengthSquared(direction) < 1.0f) {
        direction = jt::Vector2f { 0.0f, -1.0f };
    }
    jt::MathHelper::normalizeMe(direction);
    auto const translation = direction * rayLength;

    auto const result = b2World_CastRayClosest(m_world->getWorldId(),
        jt::Conversion::vec(rayOrigin), jt::Conversion::vec(translation), b2DefaultQueryFilter());

    m_rayHit = nullptr;
    m_rayEnd = rayOrigin + translation;
    if (result.hit) {
        m_rayEnd = jt::Conversion::vec(result.point);
        m_rayHit = PhysicsBody::fromShape(result.shapeId);
    }
}

void SceneBox2DQueries::updateBodies(float const elapsed)
{
    for (auto const& physicsBody : m_bodies) {
        std::optional<jt::Color> highlightColor {};
        if (std::find(m_queryHits.cbegin(), m_queryHits.cend(), physicsBody.get())
            != m_queryHits.cend()) {
            highlightColor = queryHitColor;
        }
        if (physicsBody.get() == m_rayHit) {
            highlightColor = rayHitColor;
        }
        physicsBody->setHighlightColor(highlightColor);
        physicsBody->update(elapsed);
    }
}

void SceneBox2DQueries::doUpdate(float const elapsed)
{
    auto const mousePosition = mouse()->getMousePositionWorld();
    if (mouse()->justPressed(jt::MouseButtonCode::MBLeft) && m_bodies.size() < maxNumberOfBodies) {
        createBody(mousePosition);
    }

    if (keyboard()->pressed(jt::KeyCode::Q)) {
        m_queryRotation -= queryRotationSpeed * elapsed;
    }
    if (keyboard()->pressed(jt::KeyCode::E)) {
        m_queryRotation += queryRotationSpeed * elapsed;
    }

    int const subStepCount = 4;
    m_world->step(elapsed, subStepCount);

    flashContacts();
    queryQuad(mousePosition);
    castRay(mousePosition);
    updateBodies(elapsed);

    m_queryShape->setPosition(mousePosition);
    m_queryShape->setRotation(m_queryRotation);
    m_queryShape->update(elapsed);
    m_rayLine->setLineVector(m_rayEnd - rayOrigin);
    m_rayLine->update(elapsed);
    m_rayHitMarker->setPosition(m_rayEnd);
    m_rayHitMarker->update(elapsed);

    m_info->setText("Click: add body. Q/E: rotate. Quad hits: " + std::to_string(m_queryHits.size())
        + ", ray hit: " + (m_rayHit ? "body" : "wall"));
    m_info->update(elapsed);
}

void SceneBox2DQueries::doDraw() const
{
    for (auto const& physicsBody : m_bodies) {
        physicsBody->draw();
    }
    m_queryShape->draw(renderTarget());
    m_rayLine->draw(renderTarget());
    m_rayHitMarker->draw(renderTarget());
    m_info->draw(renderTarget());
}

std::string SceneBox2DQueries::getName() const { return "Box2D contacts, shape query, ray cast"; }
