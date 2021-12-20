#ifndef STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD

#include "bar.hpp"
#include "box2dwrapper/box2d_world_interface.hpp"
#include "game_state.hpp"
#include "shape.hpp"
#include "vector.hpp"

class StateBox2d : public jt::GameState {
private:
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };

    jt::Bar::Sptr m_bar1;
    jt::Bar::Sptr m_bar2;
    std::string getName() const override;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;

    void CreateWalls();
    void CreateOneWall(jt::Vector2f const& pos);
    void CreatePlayer();
};

#endif
