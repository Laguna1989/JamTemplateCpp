#include "action_commands/action_command_manager.hpp"
#include "audio/audio_null.hpp"
#include "camera.hpp"
#include "game.hpp"
#include "game_state.hpp"
#include "gfx_null.hpp"
#include "input/input_manager_null.hpp"
#include "logging/logger_null.hpp"
#include "render_window_null.hpp"
#include "shape.hpp"
#include "state_manager/state_manager.hpp"
#include "system_helper.hpp"
#include "tweens/tween_color.hpp"
#include <benchmark/benchmark.h>
#include <memory>
#include <vector>

class StateTweenPerformanceTest : public jt::GameState {
private:
    std::vector<std::shared_ptr<jt::Shape>> m_shapes;
    void doInternalCreate() override
    {
        std::size_t const number_of_objects = 20U;
        for (std::size_t i = 0U; i != number_of_objects; ++i) {
            auto shape = std::make_shared<jt::Shape>();
            shape->makeRect(jt::Vector2f { 40.0f, 40.0f }, getGame()->gfx().textureManager());
            m_shapes.push_back(shape);
        }
    }
    void doInternalUpdate(float elapsed) override
    {
        for (auto s : m_shapes) {
            s->update(elapsed);
        }

        auto shape = *jt::SystemHelper::select_randomly(m_shapes.cbegin(), m_shapes.cend());
        auto tw = jt::TweenColor::create(shape, 1.0f, jt::colors::Red, jt::colors::White);
        add(tw);
    }

public:
    std::string getName() const override { return "Performance Tweens"; }

private:
    void doInternalDraw() const override
    {
        for (auto s : m_shapes) {
            s->draw(getGame()->gfx().target());
        }
    }
};

static void BM_GamestateWithTweeningShapes(benchmark::State& state)
{
    for (auto _ : state) {
        jt::null_objects::GfxNull gfx;
        jt::InputManagerNull input;
        jt::AudioNull audio;

        jt::StateManager stateManager { std::make_shared<StateTweenPerformanceTest>() };
        jt::null_objects::LoggerNull logger;
        jt::ActionCommandManager actionCommandManager { logger };
        auto game = std::make_shared<jt::Game>(
            gfx, input, audio, stateManager, logger, actionCommandManager);
        game->getStateManager().update(game, 0);
        for (int i = 0; i != 500; ++i) {
            game->update(0.02f);
            game->draw();
        }
    }
}

BENCHMARK(BM_GamestateWithTweeningShapes)->Unit(benchmark::kMillisecond);
