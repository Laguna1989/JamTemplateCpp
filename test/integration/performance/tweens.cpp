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
#include <system_helper.hpp>
#include <tweens/tween_color.hpp>
#include <benchmark/benchmark.h>
#include <memory>
#include <vector>

class StateTweenPerformanceTest : public jt::GameState {
private:
    std::vector<std::shared_ptr<jt::Shape>> m_shapes;

    void onCreate() override
    {
        std::size_t const number_of_objects = 20u;
        for (std::size_t i = 0u; i != number_of_objects; ++i) {
            auto shape = std::make_shared<jt::Shape>();
            shape->makeRect(jt::Vector2f { 40.0f, 40.0f }, textureManager());
            m_shapes.push_back(shape);
        }
    }

    void onEnter() override { }

    void onUpdate(float elapsed) override
    {
        for (auto s : m_shapes) {
            s->update(elapsed);
        }

        auto const shape = jt::SystemHelper::select_randomly(m_shapes);
        auto const tw = jt::TweenColor::create(shape, 1.0f, jt::colors::Red, jt::colors::White);
        add(tw);
    }

public:
    std::string getName() const override { return "Performance Tweens"; }

private:
    void onDraw() const override
    {
        for (auto s : m_shapes) {
            s->draw(renderTarget());
        }
    }
};

static void BM_GamestateWithTweeningShapes(benchmark::State& state)
{
    for (auto _ : state) {
        jt::null_objects::GfxNull gfx;
        jt::InputManagerNull input;
        jt::null_objects::AudioNull audio;

        jt::StateManager stateManager { std::make_shared<StateTweenPerformanceTest>() };
        jt::null_objects::LoggerNull logger;
        jt::ActionCommandManager actionCommandManager { logger };
        jt::CacheNull cache;

        auto game = std::make_shared<jt::Game>(
            gfx, input, audio, stateManager, logger, actionCommandManager, cache);
        game->stateManager().update(game, 0);
        for (int i = 0; i != 500; ++i) {
            game->update(0.02f);
            game->draw();
        }
    }
}

BENCHMARK(BM_GamestateWithTweeningShapes)->Unit(benchmark::kMillisecond);
