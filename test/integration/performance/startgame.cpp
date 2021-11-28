#include "camera.hpp"
#include "game.hpp"
#include "game_state.hpp"
#include "input/input_manager_null.hpp"
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
        m_shape->makeRect({ 20.0f, 20.0f });
    }
    void doInternalUpdate(float elapsed) override { m_shape->update(elapsed); }
    void doInternalDraw() const override { m_shape->draw(getGame()->getRenderTarget()); }
};

static void BM_StartGame(benchmark::State& state)
{
    for (auto _ : state) {
        std::shared_ptr<jt::null_objects::RenderWindowNull> window
            = std::make_shared<jt::null_objects::RenderWindowNull>(800, 600, "jt_performance");
        std::shared_ptr<jt::StateManager> stateManager
            = std::make_shared<jt::StateManager>(std::make_shared<StateEmpty>());
        auto game = std::make_shared<jt::Game>(window, std::make_shared<jt::InputManagerNull>(),
            std::make_shared<jt::MusicPlayerNull>(), std::make_shared<jt::Camera>(1.0f),
            stateManager);
        stateManager->checkAndPerformSwitchState(game);
        game->update(0.02f);
        game->draw();
    }
}

BENCHMARK(BM_StartGame)->Unit(benchmark::kMillisecond);
