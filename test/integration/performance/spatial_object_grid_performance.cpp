#include <random/random.hpp>
#include <spatial_object_grid.hpp>
#include <benchmark/benchmark.h>

struct TestObject {
    jt::Vector2f getPosition() const { return m_position; }
    void setPosition(jt::Vector2f const& newPosition) { m_position = newPosition; }
    jt::Vector2f m_position {};
};

static void BM_UpdateSpatialObjectGrid(benchmark::State& state)
{
    auto numberOfObjects = 100u;
    jt::SpatialObjectGrid<TestObject, 16> grid;
    std::vector<std::shared_ptr<TestObject>> objects;
    objects.resize(numberOfObjects);

    for (auto _ : state) {
        for (auto i = 0u; i != numberOfObjects; ++i) {
            auto object = std::make_shared<TestObject>();
            object->m_position
                = jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f });
            objects.push_back(object);
            grid.push_back(object);
        }

        for (auto i = 0u; i != 10; ++i) {
            grid.getObjectsAround(
                jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f }), 16.0f);
        }

        for (auto i = 0u; i != 30; ++i) {
            objects[i]->m_position
                = jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f });
        }

        grid.update(0.1f);

        for (auto i = 0u; i != 10; ++i) {
            grid.getObjectsAround(
                jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f }), 16.0f);
        }
    }
}

BENCHMARK(BM_UpdateSpatialObjectGrid)->Unit(benchmark::kMillisecond);
