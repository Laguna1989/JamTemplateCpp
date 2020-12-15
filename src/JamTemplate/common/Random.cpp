#include "Random.hpp"
#include <stdexcept>
#include <time.h>

using namespace jt;

std::default_random_engine Random::m_engine;

int Random::getInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_engine);
}

float Random::getFloat(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_engine);
}

float Random::getFloatGauss(float mu, float sigma)
{
    if (sigma <= 0) {
        throw std::invalid_argument { "sigma must be than larger zero for gauss distribution" };
    }
    std::normal_distribution<float> dist(mu, sigma);
    return dist(m_engine);
}

bool Random::getChance(float c) { return (getFloat(0.0f, 1.0f) <= c); }

jt::Color const Random::getRandomColor()
{
    std::uint8_t const r = static_cast<std::uint8_t>(getInt(0, 255));
    std::uint8_t const g = static_cast<std::uint8_t>(getInt(0, 255));
    std::uint8_t const b = static_cast<std::uint8_t>(getInt(0, 255));
    return jt::Color { r, g, b };
}

jt::Vector2 const Random::getRandomPointin(jt::Rect r)
{
    auto const x = getFloat(r.left(), r.left() + r.width());
    auto const y = getFloat(r.top(), r.top() + r.height());
    return jt::Vector2 { x, y };
}

void Random::setSeed(unsigned int s) { m_engine.seed(s); }

void Random::useTimeAsRandomSeed() { setSeed(static_cast<unsigned int>(time(NULL))); }
