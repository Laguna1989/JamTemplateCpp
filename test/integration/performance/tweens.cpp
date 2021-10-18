#include "game.hpp"
#include "game_state.hpp"
#include "shape.hpp"
#include "system_helper.hpp"
#include "tween_color.hpp"
#include <benchmark/benchmark.h>
#include <memory>
#include <vector>

class StateTweenPerformanceTest : public jt::GameState {
public:
    StateTweenPerformanceTest(std::size_t numberOfObjects)
        : m_numberOfObjects { numberOfObjects }
    {
    }

private:
    std::size_t m_numberOfObjects { 1 };
    std::vector<std::shared_ptr<jt::Shape>> m_shapes;
    void doInternalCreate() override
    {
        for (std::size_t i = 0U; i != m_numberOfObjects; ++i) {
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

        auto tw
            = jt::TweenColor<jt::Shape>::create(shape, 1.0f, jt::colors::Red, jt::colors::White);
        add(tw);
    }

    void doInternalDraw() const override
    {
        for (auto s : m_shapes) {
            s->draw(nullptr);
        }
    }
};

static void BM_GamestateWithTweeningShapes(benchmark::State& state)
{
    for (auto _ : state) {
        auto game = std::make_shared<jt::Game>(nullptr, 1.0f, nullptr, nullptr);

        auto gs = std::make_shared<StateTweenPerformanceTest>(20U);
        game->switchState(gs);
        for (int i = 0; i != 500; ++i) {
            game->update(0.166f);
            game->draw();
        }
    }
}

BENCHMARK(BM_GamestateWithTweeningShapes);
