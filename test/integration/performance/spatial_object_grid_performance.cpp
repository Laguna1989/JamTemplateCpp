#include <random/random.hpp>
#include <spatial_object_grid.hpp>
#include <benchmark/benchmark.h>
#include <iostream>

struct TestObjectB {
    jt::Vector2f getPosition() const { return m_position; }
    void setPosition(jt::Vector2f const& newPosition) { m_position = newPosition; }
    jt::Vector2f m_position {};
    void perform() { m_a++; }
    static unsigned long long m_a;
};

unsigned long long TestObjectB::m_a { 0ull };

static void BM_UpdateSpatialObjectGrid(benchmark::State& state)
{
    auto numberOfObjects = 100u;
    jt::SpatialObjectGrid<TestObjectB, 16> grid;
    std::vector<std::shared_ptr<TestObjectB>> objects;
    objects.resize(numberOfObjects);

    for (auto _ : state) {
        for (auto i = 0u; i != numberOfObjects; ++i) {
            auto object = std::make_shared<TestObjectB>();
            object->m_position
                = jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f });
            objects[i] = object;
            grid.push_back(object);
        }

        for (auto i = 0u; i != 10; ++i) {
            auto objects = grid.getObjectsAround(
                jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f }), 16.0f);
            for (auto& o : objects) {
                o.lock()->perform();
            }
        }

        for (auto i = 0u; i != 30; ++i) {
            objects[i]->m_position
                = jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f });
        }

        grid.update(0.1f);

        for (auto i = 0u; i != 10; ++i) {
            auto objects = grid.getObjectsAround(
                jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f }), 16.0f);
            for (auto& o : objects) {
                o.lock()->perform();
            }
        }
    }
    std::cout << TestObjectB::m_a << "\n";
    TestObjectB::m_a = 0ull;
}

BENCHMARK(BM_UpdateSpatialObjectGrid)->Unit(benchmark::kMillisecond);
