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

jt::color const Random::getRandomColor()
{
    std::uint8_t r = static_cast<std::uint8_t>(getInt(0, 255));
    std::uint8_t g = static_cast<std::uint8_t>(getInt(0, 255));
    std::uint8_t b = static_cast<std::uint8_t>(getInt(0, 255));
    return jt::color { r, g, b };
}

jt::vector2 const Random::getRandomPointin(jt::rect r)
{
    auto x = getFloat(r.left(), r.left() + r.width());
    auto y = getFloat(r.top(), r.top() + r.height());

    return jt::vector2 { x, y };
}

void Random::setSeed(unsigned int s) { m_engine.seed(s); }

void Random::useTimeAsRandomSeed() { setSeed(static_cast<unsigned int>(time(NULL))); }
