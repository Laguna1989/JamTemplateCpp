#include "action_commands/action_command_manager.hpp"
#include "camera.hpp"
#include "game.hpp"
#include "game_state.hpp"
#include "input/input_manager_null.hpp"
#include "logging/logger_null.hpp"
#include "music_player_null.hpp"
#include "render_window_null.hpp"
#include "shape.hpp"
#include "state_manager.hpp"
#include "tweens/tween_color.hpp"
#include <benchmark/benchmark.h>
#include <memory>
#include <vector>

class StateEmpty : public jt::GameState {
private:
    std::shared_ptr<jt::Shape> m_shape;
    void doInternalCreate() override
    {
        m_shape = std::make_shared<jt::Shape>();
        m_shape->makeRect({ 20.0f, 20.0f }, getGame()->gfx().textureManager());
    }
    void doInternalUpdate(float elapsed) override { m_shape->update(elapsed); }
    void doInternalDraw() const override { m_shape->draw(getGame()->getRenderTarget()); }

public:
    std::string getName() const override { return "Performance StartGame"; }
};

static void BM_StartGame(benchmark::State& state)
{
    for (auto _ : state) {
        jt::null_objects::RenderWindowNull window { 800, 600, "jt_performance" };
        jt::StateManager stateManager { std::make_shared<StateEmpty>() };
        jt::InputManagerNull input;
        jt::MusicPlayerNull music;
        jt::Camera camera { 1.0f };
        jt::null_objects::LoggerNull logger;
        jt::ActionCommandManager actionCommandManager { logger };
        auto game = std::make_shared<jt::Game>(
            window, input, music, camera, stateManager, logger, actionCommandManager);
        stateManager.checkAndPerformSwitchState(game);
        game->update(0.02f);
        game->draw();
    }
}

BENCHMARK(BM_StartGame)->Unit(benchmark::kMillisecond);
