#ifndef STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "MovementObject.hpp"
#include "SmartBar.hpp"
#include "SmartShape.hpp"
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

class StateBox2d : public jt::GameState {
public:
    StateBox2d()
        : m_world { std::make_shared<b2World>(b2Vec2 { 0, 0.02f }) }
    {
    }

private:
    std::shared_ptr<b2World> m_world { nullptr };

    jt::SmartBar::Sptr m_bar1;
    jt::SmartBar::Sptr m_bar2;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;

    void CreateWalls();
    void CreateOneWall(jt::Vector2 const& pos);
    void CreatePlayer();
};

#endif
