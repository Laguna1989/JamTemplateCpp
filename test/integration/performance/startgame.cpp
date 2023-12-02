#include <action_commands/action_command_manager.hpp>
#include <audio/audio/audio_null.hpp>
#include <cache/cache_null.hpp>
#include <camera.hpp>
#include <game.hpp>
#include <game_state.hpp>
#include <graphics/gfx_null.hpp>
#include <graphics/render_window_null.hpp>
#include <input/input_manager_null.hpp>
#include <log/logger_null.hpp>
#include <shape.hpp>
#include <state_manager/state_manager.hpp>
#include <tweens/tween_color.hpp>
#include <benchmark/benchmark.h>
#include <memory>
#include <vector>

class StateEmpty : public jt::GameState {
private:
    std::shared_ptr<jt::Shape> m_shape;

    void onCreate() override
    {
        m_shape = std::make_shared<jt::Shape>();
        m_shape->makeRect({ 20.0f, 20.0f }, textureManager());
    }

    void onEnter() override { }

    void onUpdate(float elapsed) override { m_shape->update(elapsed); }

    void onDraw() const override { m_shape->draw(renderTarget()); }

public:
    std::string getName() const override { return "Performance StartGame"; }
};

static void BM_StartGame(benchmark::State& state)
{
    for (auto _ : state) {
        jt::null_objects::GfxNull gfx;
        jt::StateManager stateManager { std::make_shared<StateEmpty>() };
        jt::InputManagerNull input;
        jt::null_objects::AudioNull audio;

        jt::null_objects::LoggerNull logger;
        jt::ActionCommandManager actionCommandManager { logger };
        jt::CacheNull cache;
        auto game = std::make_shared<jt::Game>(
            gfx, input, audio, stateManager, logger, actionCommandManager, cache);
        stateManager.update(game, 0);
        game->update(0.02f);
        game->draw();
    }
}

BENCHMARK(BM_StartGame)->Unit(benchmark::kMillisecond);
