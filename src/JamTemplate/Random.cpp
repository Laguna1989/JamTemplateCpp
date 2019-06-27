#include "Random.hpp"

using namespace JamTemplate;

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
    std::normal_distribution<float> dist(mu, sigma);
    return dist(m_engine);
}
bool Random::getChance(float c)
{
    return (getFloat(0.0f, 1.0f) <= c);
}

sf::Color const Random::getRandomColor()
{
    sf::Uint8 r = static_cast<sf::Uint8>(getInt(0, 255));
    sf::Uint8 g = static_cast<sf::Uint8>(getInt(0, 255));
    sf::Uint8 b = static_cast<sf::Uint8>(getInt(0, 255));
    return sf::Color { r, g, b };
}

sf::Vector2f const Random::getRandomPointin(sf::FloatRect r)
{
    auto x = getFloat(r.left, r.left + r.width);
    auto y = getFloat(r.top, r.top + r.height);

    return sf::Vector2f { x, y };
}
