#include "mocks/mock_game.hpp"
#include "particle_system.hpp"
#include "sdl_setup.hpp"
#include "shape.hpp"
#include "texture_manager_impl.hpp"
#include <gtest/gtest.h>

TEST(ParticleSystemTest, InitIsCalledForEveryParticle)
{
    int numberOfInitCalls = 0;

    jt::ParticleSystem<jt::Shape, 5> ps(
        [&numberOfInitCalls]() {
            numberOfInitCalls++;
            return std::shared_ptr<jt::Shape>();
        },
        [](auto /*s*/) {});

    ASSERT_EQ(numberOfInitCalls, 5);
}

TEST(ParticleSystemTest, ResetNotCalledOnConstruction)
{
    int numberofResetCalls = 0;

    jt::ParticleSystem<jt::Shape, 5> ps([]() { return std::shared_ptr<jt::Shape>(); },
        [&numberofResetCalls](auto /*s*/) { numberofResetCalls++; });

    ASSERT_EQ(numberofResetCalls, 0);
}

TEST(ParticleSystemTest, ResetCalledOnFire)
{
    int numberofResetCalls = 0;

    jt::ParticleSystem<jt::Shape, 5> ps([]() { return std::shared_ptr<jt::Shape>(); },
        [&numberofResetCalls](auto /*s*/) { numberofResetCalls++; });

    ps.Fire(4);
    ASSERT_EQ(numberofResetCalls, 4);
}

TEST(ParticleSystemTest, ResetCalledMultipleTimes)
{
    int numberofResetCalls = 0;

    jt::ParticleSystem<jt::Shape, 5> ps([]() { return std::shared_ptr<jt::Shape>(); },
        [&numberofResetCalls](auto /*s*/) { numberofResetCalls++; });

    ps.Fire(10);
    ps.Fire(10);
    ps.Fire(10);
    ps.Fire(10);
    ASSERT_EQ(numberofResetCalls, 40);
}

TEST(ParticleSystemTest, CreateDoesNotRaiseExceptionWhenGameInstanceIsSet)
{
    auto g = std::make_shared<::testing::NiceMock<MockGame>>();
    EXPECT_CALL(g->m_gfx, target()).WillRepeatedly(::testing::Return(nullptr));

    jt::ParticleSystem<jt::Shape, 5> ps(
        []() {
            auto s = std::make_shared<jt::Shape>();
            s->makeRect({ 1, 1 }, getTextureManager());
            return s;
        },
        [](auto /*s*/) {});

    ps.setGameInstance(g);
    ASSERT_NO_THROW(ps.create());
}

TEST(ParticleSystemTest, UpdateCallDoesNotRaiseException)
{
    jt::ParticleSystem<jt::Shape, 5> ps(
        []() {
            auto s = std::make_shared<jt::Shape>();
            s->makeRect({ 1, 1 }, getTextureManager());
            return s;
        },
        [](auto /*s*/) {});

    ps.Fire(5);

    ASSERT_NO_THROW(ps.update(1.0f));
}

TEST(ParticleSystemTest, DrawWithGame)
{
    auto g = std::make_shared<::testing::NiceMock<MockGame>>();
    EXPECT_CALL(g->m_gfx, target()).WillRepeatedly(::testing::Return(nullptr));
    jt::ParticleSystem<jt::Shape, 5> ps(
        []() {
            auto s = std::make_shared<jt::Shape>();
            s->makeRect({ 1, 1 }, getTextureManager());
            return s;
        },
        [](auto /*s*/) {});

    ps.setGameInstance(g);
    ps.Fire(5);
    ps.update(0.1f);
    ASSERT_NO_THROW(ps.draw());
}
