#include <animation.hpp>
#include <graphics/gfx_null.hpp>
#include <math_helper.hpp>
#include <random/random.hpp>
#include <shape.hpp>
#include <array>
#include <benchmark/benchmark.h>

constexpr std::size_t arraySize { 50u };
constexpr std::size_t numberOfIterationLoops { 100u };

static void BM_UpdateDrawablePositions(benchmark::State& state)
{
    jt::null_objects::GfxNull gfx;
    jt::TextureManagerImpl tm(gfx.target()->get(0));

    std::array<jt::Shape, arraySize> shapes;
    for (auto& s : shapes) {
        s.makeRect(jt::Vector2f { 32.0f, 16.0f }, gfx.textureManager());
    }

    std::array<jt::Animation, arraySize> animations;
    for (auto& a : animations) {
        a.add("assets/test/integration/performance/coin.png", "idle", jt::Vector2u { 16, 16 },
            jt::MathHelper::numbersBetween(0u, 11u), 0.15f, gfx.textureManager());
        a.play("idle");
    }

    auto const idsToChange
        = jt::MathHelper::numbersBetween(0u, static_cast<unsigned int>(arraySize / 3u));
    for (auto _ : state) {

        for (auto i = 0u; i != numberOfIterationLoops; ++i) {
            auto const pos
                = jt::Random::getRandomPointIn(jt::Rectf { -100.0f, -100.0f, 100.0f, 100.0f });
            auto const camPos
                = jt::Random::getRandomPointIn(jt::Rectf { -100.0f, -100.0f, 100.0f, 100.0f });
            jt::DrawableImpl::setCamOffset(camPos);

            // change position for first third of the objects.
            for (auto i : idsToChange) {
                shapes[i].setPosition(pos);
                animations[i].setPosition(pos);
            }

            for (auto& s : shapes) {
                s.update(0.1f);
            }
            for (auto& a : animations) {
                a.update(0.1f);
            }
        }
    }
}

BENCHMARK(BM_UpdateDrawablePositions)->Unit(benchmark::kMillisecond);
