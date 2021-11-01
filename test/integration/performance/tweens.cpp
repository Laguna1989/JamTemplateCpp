#include "game.hpp"
#include "game_state.hpp"
#include "shape.hpp"
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
            shape->makeRect(jt::Vector2 { 40.0f, 40.0f });
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

    void doInternalDraw() const override
    {
        for (auto s : m_shapes) {
            s->draw(getGame()->getRenderTarget());
        }
    }
};

static void BM_GamestateWithTweeningShapes(benchmark::State& state)
{
    for (auto _ : state) {
        auto game = std::make_shared<jt::Game>(nullptr, 1.0f, nullptr, nullptr);

        auto gs = std::make_shared<StateTweenPerformanceTest>();
        game->switchState(gs);
        for (int i = 0; i != 500; ++i) {
            game->update(0.02f);
            game->draw();
        }
    }
}

BENCHMARK(BM_GamestateWithTweeningShapes)->Unit(benchmark::kMillisecond);
