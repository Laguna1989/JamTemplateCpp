#include "random.hpp"
#include <ctime>
#include <stdexcept>

namespace jt {
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

jt::Color Random::getRandomColor()
{
    auto const r = static_cast<std::uint8_t>(getInt(0, 255));
    auto const g = static_cast<std::uint8_t>(getInt(0, 255));
    auto const b = static_cast<std::uint8_t>(getInt(0, 255));
    return jt::Color { r, g, b };
}

jt::Vector2f Random::getRandomPointIn(jt::Rectf rect)
{
    auto const x = getFloat(rect.left, rect.left + rect.width);
    auto const y = getFloat(rect.top, rect.top + rect.height);
    return jt::Vector2f { x, y };
}

void Random::setSeed(unsigned int s) { m_engine.seed(s); }

void Random::useTimeAsRandomSeed() { setSeed(static_cast<unsigned int>(time(nullptr))); }

jt::Color Random::getRandomColorHSV(
    float hmin, float hmax, float smin, float smax, float vmin, float vmax)
{
    return jt::MakeColor::FromHSV(jt::Random::getFloat(hmin, hmax),
        jt::Random::getFloat(smin, smax), jt::Random::getFloat(vmin, vmax));
}
} // namespace jt
