#include "random.hpp"
#include <color/color_factory.hpp>
#include <vector_factory.hpp>
#include <ctime>
#include <stdexcept>

std::default_random_engine jt::Random::m_engine;

int jt::Random::getInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_engine);
}

float jt::Random::getFloat(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_engine);
}

float jt::Random::getFloatGauss(float mu, float sigma)
{
    if (sigma <= 0) {
        throw std::invalid_argument { "sigma must be larger than zero for gauss distribution" };
    }
    std::normal_distribution<float> dist(mu, sigma);
    return dist(m_engine);
}

bool jt::Random::getChance(float c) { return (getFloat(0.0f, 1.0f) <= c); }

jt::Color jt::Random::getRandomColor()
{
    auto const r = static_cast<std::uint8_t>(getInt(0, 255));
    auto const g = static_cast<std::uint8_t>(getInt(0, 255));
    auto const b = static_cast<std::uint8_t>(getInt(0, 255));
    return jt::Color { r, g, b };
}

jt::Vector2f jt::Random::getRandomPointIn(Rectf const& rect)
{
    auto const x = getFloat(rect.left, rect.left + rect.width);
    auto const y = getFloat(rect.top, rect.top + rect.height);
    return jt::Vector2f { x, y };
}

jt::Vector2f jt::Random::getRandomPointIn(jt::Vector2f const& size)
{
    return getRandomPointIn(jt::Rectf { 0.0f, 0.0f, size.x, size.y });
}

jt::Vector2f jt::Random::getRandomPointInCircle(float radius)
{
    float const range = getFloat(0, radius);
    float const angle = getFloat(0, 360.0f);
    return jt::VectorFactory::fromPolar(range, angle);
}

jt::Vector2f jt::Random::getRandomPointOnCircle(float radius)
{
    float const angle = getFloat(0, 360.0f);
    return jt::VectorFactory::fromPolar(radius, angle);
}

void jt::Random::setSeed(unsigned int s) { m_engine.seed(s); }

void jt::Random::useTimeAsRandomSeed() { setSeed(static_cast<unsigned int>(time(nullptr))); }

jt::Color jt::Random::getRandomColorHSV(
    float hmin, float hmax, float smin, float smax, float vmin, float vmax)
{
    return jt::ColorFactory::fromHSV(jt::Random::getFloat(hmin, hmax),
        jt::Random::getFloat(smin, smax), jt::Random::getFloat(vmin, vmax));
}
