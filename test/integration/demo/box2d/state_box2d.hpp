#ifndef STRESSTEST_STATE_BOX2D_HPP
#define STRESSTEST_STATE_BOX2D_HPP

#include "box2dwrapper/box2d_object.hpp"
#include "tilemap/tile_layer.hpp"
#include <bar.hpp>
#include <box2d/movement_object.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_state.hpp>
#include <shape.hpp>
#include <vector.hpp>

class StateBox2d : public jt::GameState {
private:
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };
    std::vector<std::shared_ptr<jt::Box2DObject>> m_colliders {};
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround { nullptr };
    std::shared_ptr<Player> m_player { nullptr };

    std::string getName() const override;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;

    void CreatePlayer();
    void loadLevel();
};

#endif
