#include "game.hpp"
#include "game_object.hpp"
#include "game_state.hpp"
#include "random.hpp"
#include "sprite.hpp"
#include "tween_color.hpp"
#include <benchmark/benchmark.h>
#include <memory>
#include <vector>

class GameObjectInstance : public ::jt::GameObject {
private:
    std::shared_ptr<jt::Sprite> m_sprite;
    void doCreate() override
    {
        m_sprite = std::make_shared<jt::Sprite>();
        m_sprite->loadSprite("assets/coin.png");
    };
    void doUpdate(float const elapsed) override
    {
        m_sprite->setPosition(jt::Random::getRandomPointin(jt::Rect { 0, 0, 100, 100 }));
        m_sprite->setRotation(getAge() * 5.0f);
        m_sprite->setScale(jt::Random::getRandomPointin(jt::Rect { 0.5f, 0.5f, 1.0f, 1.0f }));
        m_sprite->update(elapsed);
        if (getAge() >= 1.0f) {
            kill();
        }
    };
    void doDraw() const override { m_sprite->draw(getGame()->getRenderTarget()); };
    void doKill() override {};
};

class StateObjectsPerformanceTest : public jt::GameState {
private:
    std::vector<std::shared_ptr<GameObjectInstance>> m_objects;
    void doInternalCreate() override { }
    void doInternalUpdate(float elapsed) override
    {
        spawnObject();
        spawnObject();
    }
    void spawnObject()
    {
        auto obj = std::make_shared<GameObjectInstance>();
        add(obj);
    }

    void doInternalDraw() const override { }
};

static void BM_GamestateWithObjects(benchmark::State& state)
{
    auto game = std::make_shared<jt::Game>(nullptr, 1.0f, nullptr, nullptr);

    for (auto _ : state) {
        auto gs = std::make_shared<StateObjectsPerformanceTest>();
        game->switchState(gs);
        for (int i = 0; i != 500; ++i) {
            game->update(0.02f);
            game->draw();
        }
    }
}

BENCHMARK(BM_GamestateWithObjects);
