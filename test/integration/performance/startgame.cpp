#include "game.hpp"
#include "game_state.hpp"
#include "render_window_null.hpp"
#include "shape.hpp"
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
        auto game = std::make_shared<jt::Game>(
            std::make_shared<jt::null_objects::RenderWindowNull>(800, 600, "jt_performance"), 1.0f,
            nullptr, nullptr);
        auto gs = std::make_shared<StateEmpty>();
        game->switchState(gs);
        game->update(0.02f);
        game->draw();
    }
}

BENCHMARK(BM_StartGame)->Unit(benchmark::kMillisecond);
