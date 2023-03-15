#ifndef DEMO_STATE_PLATFORMER_HPP
#define DEMO_STATE_PLATFORMER_HPP

#include <box2d/contact_callback_player_enemy.hpp>
#include <box2d/contact_callback_player_ground.hpp>
#include <box2d/level.hpp>
#include <box2d/platform_player.hpp>
#include <box2dwrapper/box2d_object.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_state.hpp>
#include <particle_system.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <tilemap/tile_layer.hpp>
#include <vector.hpp>

class StatePlatformer : public jt::GameState {
public:
    explicit StatePlatformer(std::string const& levelName = "platformer_0_0.json");

private:
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };

    std::string m_levelName { "" };
    std::shared_ptr<Level> m_level { nullptr };
    std::shared_ptr<Player> m_player { nullptr };
    std::shared_ptr<jt::Vignette> m_vignette { nullptr };

    std::shared_ptr<jt::ParticleSystem<jt::Shape, 50>> m_walkParticles { nullptr };
    std::shared_ptr<jt::ParticleSystem<jt::Shape, 50>> m_playerJumpParticles { nullptr };

    bool m_ending { false };

    std::string getName() const override;

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const /*elapsed*/) override;
    void onDraw() const override;

    void CreatePlayer();
    void loadLevel();
    void handleCameraScrolling(float const elapsed);
    void endGame();
    void createPlayerWalkParticles();
    void createPlayerJumpParticleSystem();
};

#endif // DEMO_STATE_PLATFORMER_HPP
