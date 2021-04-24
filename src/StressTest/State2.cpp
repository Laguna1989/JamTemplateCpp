#include "State2.hpp"
#include "DrawableHelpers.hpp"
#include "GameInterface.hpp"
#include "InputManager.hpp"
#include "StateSelect.hpp"

void State2::doInternalCreate()
{
    using jt::Shape;
    using jt::TweenAlpha;

    m_sky = jt::dh::createRectShape(jt::Vector2 { 400, 300 }, jt::Color { 178, 255, 255 });

    m_overlay = jt::dh::createRectShape(jt::Vector2 { 400, 300 }, jt::colors::Black);
    m_overlay->update(0.0f);

    auto tw = TweenAlpha<Shape>::create(m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
    add(tw);

    m_SwarmObjects = std::make_shared<jt::ObjectGroup<SwarmObject>>();
    add(m_SwarmObjects);
    for (int i = 0; i != 50; ++i) {
        SwarmObject::Sptr sptr = std::make_shared<SwarmObject>();
        add(sptr);
        m_SwarmObjects->push_back(sptr);
    }

    m_sky->update(0.0f);

    setAutoDraw(false);
}

void State2::doInternalUpdate(float const elapsed)
{
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->switchState(std::make_shared<StateSelect>());
    }

    m_overlay->update(elapsed);

    updateSwarm();
}

void State2::updateSwarm()
{
    jt::Vector2 centerPos {};
    for (auto const& o : *m_SwarmObjects) {
        centerPos + centerPos + o.lock()->getPosition();
    }
    centerPos = centerPos / static_cast<float>(m_SwarmObjects->size());

    for (size_t i = 0; i != m_SwarmObjects->size(); ++i) {
        updateOneSwarmObject(i, centerPos);
    }
}

void State2::updateOneSwarmObject(const size_t& firstSwarmObjectIndex, jt::Vector2& centerPos)
{
    float cutoffDistance = 10;

    auto o1 = m_SwarmObjects->at(firstSwarmObjectIndex).lock();
    jt::Vector2 SummedUpDir { 0.0f, 0.0f };

    auto const mousePos = getGame()->input()->mouse()->getMousePositionWorld();
    auto dist = mousePos - o1->getPosition();
    jt::MathHelper::normalizeMe(dist);

    float lc = jt::MathHelper::length(centerPos - o1->getPosition());
    SummedUpDir = SummedUpDir
        + (centerPos - o1->getPosition()) / lc * 1000.0f
            / static_cast<float>(m_SwarmObjects->size());

    for (size_t secondSwarmObjectIndex = 0; secondSwarmObjectIndex != m_SwarmObjects->size();
         ++secondSwarmObjectIndex) {
        if (firstSwarmObjectIndex == secondSwarmObjectIndex)
            continue;

        auto o2 = m_SwarmObjects->at(secondSwarmObjectIndex).lock();
        auto const d = o2->getPosition() - o1->getPosition();
        auto l = jt::MathHelper::length(d);
        if (l > 2 * cutoffDistance)
            continue;
        SummedUpDir
            = SummedUpDir + o2->getVelocity() * 0.09f * o2->getSwarmWeight() / o1->getSwarmWeight();

        if (l > cutoffDistance)
            continue;
        if (l < 1.5)
            l = 1.5;
        SummedUpDir = SummedUpDir - (d / l / l * 1000.0f);
    }
    SummedUpDir = SummedUpDir + dist * 30.0f;
    o1->setVelocity(SummedUpDir);
}

void State2::doInternalDraw() const
{
    drawSky();
    drawObjects();
    m_overlay->draw(getGame()->getRenderTarget());
}

void State2::drawSky() const { m_sky->draw(getGame()->getRenderTarget()); }
