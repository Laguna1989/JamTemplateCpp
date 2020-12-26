#include "State2.hpp"
#include "InputManager.hpp"
#include "StateSelect.hpp"

void State2::doInternalCreate()
{
    m_sky = std::make_shared<jt::SmartShape>();
    m_sky->makeRect(jt::Vector2(400, 300));
    m_sky->setColor(jt::Color { 178, 255, 255 });

    using jt::SmartShape;
    using jt::TweenAlpha;

    m_overlay = std::make_shared<SmartShape>();
    m_overlay->makeRect(jt::Vector2 { 400, 300 });
    m_overlay->setColor(jt::Color { 0, 0, 0 });
    m_overlay->update(0.0f);
    auto tw
        = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
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
    if (jt::InputManager::justPressed(jt::KeyCode::F1)
        || jt::InputManager::justPressed(jt::KeyCode::Escape)) {
        getGame()->switchState(std::make_shared<StateSelect>());
    }

    m_overlay->update(elapsed);

    float cutoffDistance = 10;

    jt::Vector2 centerPos {};
    for (auto const& o : *m_SwarmObjects) {
        centerPos + centerPos + o.lock()->getPosition();
    }
    centerPos = centerPos / static_cast<float>(m_SwarmObjects->size());

    jt::Vector2 mousePos = jt::InputManager::getMousePositionWorld();

    for (size_t i = 0; i != m_SwarmObjects->size(); ++i) {
        auto o1 = m_SwarmObjects->at(i).lock();
        jt::Vector2 SummedUpDir { 0.0f, 0.0f };

        auto dist = mousePos - o1->getPosition();
        jt::MathHelper::normalizeMe(dist);

        float lc = jt::MathHelper::length(centerPos - o1->getPosition());
        SummedUpDir = SummedUpDir
            + (centerPos - o1->getPosition()) / lc * 1000.0f
                / static_cast<float>(m_SwarmObjects->size());

        for (size_t j = 0; j != m_SwarmObjects->size(); ++j) {
            if (i == j)
                continue;

            auto o2 = m_SwarmObjects->at(j).lock();
            jt::Vector2 d = o2->getPosition() - o1->getPosition();
            float l = jt::MathHelper::length(d);
            if (l > 2 * cutoffDistance)
                continue;
            SummedUpDir = SummedUpDir
                + o2->getVelocity() * 0.09f * o2->getSwarmWeight() / o1->getSwarmWeight();

            if (l > cutoffDistance)
                continue;
            if (l < 1.5)
                l = 1.5;
            SummedUpDir = SummedUpDir - (d / l / l * 1000.0f);
        }
        SummedUpDir = SummedUpDir + dist * 30.0f;
        o1->setVelocity(SummedUpDir);
    }
}

void State2::doInternalDraw() const
{
    drawSky();
    drawObjects();
    m_overlay->draw(getGame()->getRenderTarget());
}

void State2::drawSky() const { m_sky->draw(getGame()->getRenderTarget()); }
