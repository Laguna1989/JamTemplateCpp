#include <object_group.hpp>
#include <random/random.hpp>
#include <benchmark/benchmark.h>
#include <iostream>

struct TestObjectA {
    jt::Vector2f getPosition() const { return m_position; }
    void setPosition(jt::Vector2f const& newPosition) { m_position = newPosition; }
    jt::Vector2f m_position {};
    void perform() { m_a++; }
    static unsigned long long m_a;
};

unsigned long long TestObjectA::m_a { 0ull };

static void BM_UpdateObjectGroup(benchmark::State& state)
{
    auto numberOfObjects = 100u;
    jt::ObjectGroup<TestObjectA> group;
    std::vector<std::shared_ptr<TestObjectA>> objects;
    objects.resize(numberOfObjects);

    for (auto _ : state) {
        for (auto i = 0u; i != numberOfObjects; ++i) {
            auto object = std::make_shared<TestObjectA>();
            object->m_position
                = jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f });
            objects[i] = object;
            group.push_back(object);
        }

        for (auto i = 0u; i != 10; ++i) {
            for (auto& o : group) {
                o.lock()->perform();
            }
        }

        for (auto i = 0u; i != 30; ++i) {
            objects[i]->m_position
                = jt::Random::getRandomPointIn(jt::Rectf { 0.0f, 0.0f, 1024.0f, 1024.0f });
        }

        group.update(0.1f);

        for (auto i = 0u; i != 10; ++i) {
            for (auto& o : group) {
                o.lock()->perform();
            }
        }
    }
    std::cout << TestObjectA::m_a << "\n";
    TestObjectA::m_a = 0ull;
}

BENCHMARK(BM_UpdateObjectGroup)->Unit(benchmark::kMillisecond);
