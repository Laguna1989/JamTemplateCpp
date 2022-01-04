#include "state_swarmobjects.hpp"
#include "../state_select.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "input/input_manager.hpp"
#include "math_helper.hpp"
#include "state_manager/state_manager_transition_fade_to_black.hpp"
#include "timer.hpp"
#include "tweens/tween_alpha.hpp"
#include <vector>

void StateSwarmObjects::doInternalCreate()
{
    using jt::Shape;
    using jt::TweenAlpha;

    m_sky = jt::dh::createShapeRect(
        jt::Vector2f { 400, 300 }, jt::Color { 178, 255, 255 }, getGame()->gfx().textureManager());

    m_SwarmObjects = std::make_shared<jt::ObjectGroup<SwarmObject>>();
    add(m_SwarmObjects);
    for (int i = 0; i != 50; ++i) {
        SwarmObject::Sptr sptr = std::make_shared<SwarmObject>();
        add(sptr);
        m_SwarmObjects->push_back(sptr);
    }

    m_sky->update(0.0f);

    setAutoDraw(false);

    getGame()->getStateManager().setTransition(
        std::make_shared<jt::StateManagerTransitionFadeToBlack>(
            jt::Vector2f { 400.0f, 300.0f }, getGame()->gfx().textureManager()));
}

void StateSwarmObjects::doInternalUpdate(float const elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }

    updateSwarm();
}

void StateSwarmObjects::updateSwarm()
{
    jt::Vector2f centerPos {};
    for (auto const& o : *m_SwarmObjects) {
        centerPos = centerPos + o.lock()->getPosition();
    }
    centerPos = centerPos / static_cast<float>(m_SwarmObjects->size());

    for (size_t i = 0; i != m_SwarmObjects->size(); ++i) {
        updateOneSwarmObject(i);
    }
}

void StateSwarmObjects::updateOneSwarmObject(const size_t& firstSwarmObjectIndex)
{
    auto o1 = m_SwarmObjects->at(firstSwarmObjectIndex).lock();
    auto p1 = o1->getPosition();
    auto v1 = o1->getVelocity();
    auto const mousePos = getGame()->input().mouse()->getMousePositionWorld();
    auto dist = mousePos - p1;
    auto distLength = jt::MathHelper::length(dist);
    jt::MathHelper::normalizeMe(dist);

    auto const vortexForce = jt::MathHelper::rotateBy(dist, 90);
    float vortexForceStrength = distLength / 20.0f;
    jt::Vector2f SummedUpDir { dist.x * 15.0f, dist.y * 15.0f };
    SummedUpDir = SummedUpDir + vortexForce * vortexForceStrength;
    // jt::Vector2f SummedUpDir { 0.0f, 0.0f };
    for (size_t secondSwarmObjectIndex = 0; secondSwarmObjectIndex != m_SwarmObjects->size();
         ++secondSwarmObjectIndex) {
        if (firstSwarmObjectIndex == secondSwarmObjectIndex) {
            continue;
        }
        auto o2 = m_SwarmObjects->at(secondSwarmObjectIndex).lock();
        auto p2 = o2->getPosition();
        auto v2 = o2->getVelocity();

        auto springVector = p2 - p1;
        auto const r = jt::MathHelper::length(springVector);
        if (r > 100) {
            continue;
        }

        if (r != 0) {
            auto f = (springVector / r) * (r - 65.0f) * 0.75f;
            SummedUpDir = SummedUpDir + f;
        }

        auto internalFrictionForce = (v1 - v2) * 0.001f;
        SummedUpDir = SummedUpDir - internalFrictionForce;
    }

    auto velocityFrictionForce = v1 * -1.0f * 0.25f;
    SummedUpDir = SummedUpDir + velocityFrictionForce;
    o1->setAcceleration(SummedUpDir);
}

void StateSwarmObjects::doInternalDraw() const
{
    drawSky();
    drawObjects();
}

void StateSwarmObjects::drawSky() const { m_sky->draw(getGame()->gfx().target()); }
std::string StateSwarmObjects::getName() const { return "Swarm Objects"; }
