#include "state_water.hpp"
#include "math_helper.hpp"
#include <drawable_helpers.hpp>
#include <random/random.hpp>

#include <imgui.h>

#include <algorithm>
#include <execution>
#include <iostream>
#include <ranges>

constexpr inline auto numberOfParticles = 400u;
constexpr inline auto particleSize = 4.0f;

namespace {
float smoothingKernel(float radius, float dst)
{
    if (dst >= radius) {
        return 0.0f;
    }

    float volume = std::numbers::pi * std::pow(radius, 4) / 6.0f;
    return (radius - dst) * (radius - dst) / volume;
}

float smoothingKernelDerivative(float dst, float radius)
{
    if (dst > radius) {
        return 0.0f;
    }

    float scale = 12.0f / (std::numbers::pi * std::pow(radius, 4));
    return (dst - radius) * scale;
}

} // namespace

void StateWater::onCreate()
{
    shape = jt::dh::createShapeCircle(particleSize * 0.5f, jt::colors::White, textureManager());

    for (auto i = 0u; i != numberOfParticles; ++i) {

        positions.push_back(
            jt::Random::getRandomPointIn(jt::Rectf { 100, 100, 400 - 100 - 100, 300 - 100 - 100 }));
        predictedPositions.push_back({ 0.0f, 0.0f });
        velocities.push_back(jt::Vector2f { 0.0f, 0.0f });
        densities.push_back(0.0f);
    }
}

void StateWater::onEnter() { }

void StateWater::onUpdate(float elapsed)
{
    // apply gravity, calculate densities
    std::ranges::iota_view indexes((size_t)0, positions.size());
    std::for_each(
        std::execution::par_unseq, indexes.begin(), indexes.end(), [this, &elapsed](size_t i) {
            velocities[i] += elapsed * gravity;
            predictedPositions[i] = positions[i] + velocities[i] * elapsed;
        });

    std::for_each(std::execution::par_unseq, indexes.begin(), indexes.end(),
        [this, &elapsed](size_t i) { densities[i] = calculateDensity(predictedPositions[i]); });

    // calculate and apply pressure force
    std::for_each(
        std::execution::par_unseq, indexes.begin(), indexes.end(), [this, &elapsed](size_t i) {
            jt::Vector2f pressureForce = calculatePressureForce(i);
            // F = m * a , so  a = F / m

            auto pressureAcceleration = pressureForce / densities[i];
            velocities[i] += pressureAcceleration * elapsed;
        });

    std::for_each(
        std::execution::par_unseq, indexes.begin(), indexes.end(), [this, &elapsed](size_t i) {
            positions[i] += velocities[i] * elapsed;

            // resolve collisions

            if (positions[i].y > 280) {
                positions[i].y = 280;
                velocities[i].y *= -1.0f * dampingFactor;
            }
            if (positions[i].y < 20) {
                positions[i].y = 20;
                velocities[i].y *= -1.0f * dampingFactor;
            }

            if (positions[i].x > 380) {
                positions[i].x = 380;
                velocities[i].x *= -1.0f * dampingFactor;
            }
            if (positions[i].x < 20) {
                positions[i].x = 20;
                velocities[i].x *= -1.0f * dampingFactor;
            }
        });
}

void StateWater::onDraw() const
{
    for (auto i = 0u; i != numberOfParticles; ++i) {
        shape->setPosition(positions[i]);
        shape->update(0.0f);
        shape->draw(renderTarget());
    }

    ImGui::Begin("physics fun");
    ImGui::SliderFloat("gravity", &gravity.y, -200.0f, 200.0f);
    ImGui::SliderFloat("smoothing Radius", &smoothingRadius, 1.0f, 400.0f);
    ImGui::SliderFloat("mass", &mass, 0.01f, 10.0f);
    ImGui::SliderFloat("target density", &targetDensity, 0.00001, 10.0f);
    ImGui::SliderFloat("pressure multiplier", &pressureMultiplier, 0.0f, 200.0f);

    ImGui::SliderFloat("damping factor", &dampingFactor, 0.5f, 1.0f);
    ImGui::End();
}

float StateWater::calculateDensity(jt::Vector2f const& samplePoint)
{
    float density = 0.0f;

    for (auto const& position : positions) {
        float const dst = jt::MathHelper::length(position - samplePoint);
        float const influence = smoothingKernel(smoothingRadius, dst);
        density += mass * influence;
    }
    return density;
}

jt::Vector2f StateWater::calculatePressureForce(std::size_t particleIndex)
{
    jt::Vector2f pressureForce = jt::Vector2f { 0.0f, 0.0f };

    for (auto otherParticleIndex = 0u; otherParticleIndex != positions.size();
         ++otherParticleIndex) {
        if (particleIndex == otherParticleIndex)
            continue;

        auto offset = positions[otherParticleIndex] - positions[particleIndex];
        float dst = jt::MathHelper::length(offset);
        jt::Vector2f dir = (dst == 0) ? jt::Random::getRandomPointOnCircle(1.0f) : offset / dst;

        float slope = smoothingKernelDerivative(dst, smoothingRadius);
        float density = densities[otherParticleIndex];
        float sharedPressure = calculateSharedPressure(density, densities[particleIndex]);
        pressureForce += -sharedPressure * dir * slope * mass / density;
    }
    return pressureForce;
}

float StateWater::convertDensityToPressure(float density)
{
    float densityError = density - targetDensity;
    float pressure = densityError * pressureMultiplier;
    return pressure;
}

float StateWater::calculateSharedPressure(float densityA, float densityB)
{
    float pressureA = convertDensityToPressure(densityA);
    float pressureB = convertDensityToPressure(densityB);
    return (pressureA + pressureB) / 2.0f;
}
