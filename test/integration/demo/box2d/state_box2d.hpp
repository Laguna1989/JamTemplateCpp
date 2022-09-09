#ifndef DEMO_STATE_PLATFORMER_HPP
#define DEMO_STATE_PLATFORMER_HPP

#include "box2dwrapper/box2d_object.hpp"
#include "my_contact_listener.hpp"
#include "screeneffects/vignette.hpp"
#include "tilemap/tile_layer.hpp"
#include <bar.hpp>
#include <box2d/PlatformPlayer.hpp>
#include <box2d/level.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_state.hpp>
#include <shape.hpp>
#include <vector.hpp>

class StatePlatformer : public jt::GameState {
private:
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };

    std::shared_ptr<Level> m_level { nullptr };
    std::shared_ptr<Player> m_player { nullptr };
    std::shared_ptr<MyContactListener> m_contactListener { nullptr };
    std::shared_ptr<jt::Vignette> m_vignette { nullptr };
    bool m_ending { false };

    std::string getName() const override;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;

    void CreatePlayer();
    void loadLevel();
    void handleCameraScrolling(float const elapsed);
};

#endif // DEMO_STATE_PLATFORMER_HPP
