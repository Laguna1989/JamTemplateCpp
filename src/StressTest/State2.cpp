#include "State2.hpp"
#include "InputManager.hpp"
#include "StateTileson.hpp"

void State2::doInternalUpdate(float const elapsed)
{

    if (getAge() >= 5.0 || jt::InputManager::justPressed(jt::KeyCode::F1)) {
        getGame()->switchState(std::make_shared<StateTileson>());
    }

    m_overlay->update(elapsed);

    float cutoffDistance = 10;

    // jt::vector2 centerPos {};
    // for (auto const& o : *m_SwarmObjects) {
    //    //centerPos += o.lock()->getPosition();
    //}
    // centerPos /= static_cast<float>(m_SwarmObjects->size());

    // for (size_t i = 0; i != m_SwarmObjects->size(); ++i) {
    //    auto o1 = m_SwarmObjects->at(i).lock();
    //    jt::vector2 SummedUpDir {};
    //    float lc = jt::MathHelper::length(centerPos - o1->getPosition());
    //    SummedUpDir += (centerPos - o1->getPosition()) / lc * 1000.0f
    //        / static_cast<float>(m_SwarmObjects->size());
    //    for (size_t j = 0; j != m_SwarmObjects->size(); ++j) {
    //        if (i == j)
    //            continue;

    //        auto o2 = m_SwarmObjects->at(j).lock();
    //        jt::vector2 d = o2->getPosition() - o1->getPosition();
    //        float l = jt::MathHelper::length(d);
    //        if (l > 2 * cutoffDistance)
    //            continue;
    //        SummedUpDir += o2->getVelocity() * 0.09f * o2->getSwarmWeight() /
    //        o1->getSwarmWeight();

    //        if (l > cutoffDistance)
    //            continue;
    //        if (l < 1)
    //            l = 1;
    //        SummedUpDir -= d / l / l * 500.0f;
    //    }
    //    float l = jt::MathHelper::length(SummedUpDir);
    //    if (l > 4) {
    //        // std::cout << i << " " << l << std::endl;
    //    }

    //    o1->setVelocity(SummedUpDir);
    //}
}
