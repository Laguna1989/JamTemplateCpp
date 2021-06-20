#ifndef STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD

#include "bar.hpp"
#include "game_state.hpp"
#include "shape.hpp"
#include "vector.hpp"
#include <Box2D/Box2D.h>

class StateBox2d : public jt::GameState {
public:
    StateBox2d()
        : m_world { std::make_shared<b2World>(b2Vec2 { 0, 100.0f }) }
    {
    }

private:
    std::shared_ptr<b2World> m_world { nullptr };

    jt::Bar::Sptr m_bar1;
    jt::Bar::Sptr m_bar2;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;

    void CreateWalls();
    void CreateOneWall(jt::Vector2 const& pos);
    void CreatePlayer();
};

#endif
