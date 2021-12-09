#ifndef GUARD_JAMTEMPLATE_RANDOM_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_RANDOM_HPP_INCLUDEGUARD

#include "color.hpp"
#include "rect.hpp"
#include "vector.hpp"
#include <random>

namespace jt {

class Random {
public:
    /// this class shall never be instantiated, but only used as a pure-static class
    Random() = delete;

    /// Get random int
    /// \param min minimum value (inclusive)
    /// \param max maximum value (inclusive)
    /// \return a random int in [min, max]
    static int getInt(int min = 0, int max = 100);

    /// Get random float
    /// \param min minimum value (inclusive)
    /// \param max maximum value (inclusive)
    /// \return random float in [min, max]
    static float getFloat(float min = 0.0, float max = 1.0);

    /// Get random float (gauss distributed)
    /// \param mu mu value
    /// \param sigma sigma value
    /// \return random float from gauss distribution
    static float getFloatGauss(float mu = 0, float sigma = 1);

    /// random bool
    /// \param c probability, between 0 and 1
    /// \return
    static bool getChance(float c = 0.5f);

    /// Get random Color
    /// \return random color
    static jt::Color getRandomColor();

    static jt::Color getRandomColorHSV(
        float hmin, float hmax, float smin, float smax, float vmin, float vmax);

    /// Get Random point in rect
    /// \param rect the rect to contain the point
    /// \return random point in rect
    static jt::Vector2f getRandomPointIn(jt::Rectf rect);

    /// Set the seed of the rng
    /// \param s seed value
    static void setSeed(unsigned int s);

    /// Use the current time as the random seed
    static void useTimeAsRandomSeed();

private:
    static std::default_random_engine m_engine;
};

} // namespace jt
#endif
