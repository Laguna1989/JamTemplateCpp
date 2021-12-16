/**
  Open Simple Noise for C++

  Port to C++ from https://gist.github.com/KdotJPG/b1270127455a94ac5d19
  by Rickard Lundberg, 2019.
  see https://github.com/deerel/OpenSimplexNoise
*/

#ifndef GUARD_JAMTEMPLATE_RANDOM_OPEN_SIMPLEX_NOISE2D
#define GUARD_JAMTEMPLATE_RANDOM_OPEN_SIMPLEX_NOISE2D

#include <array>
#include <cstdint>
#include <random>

namespace jt {

class OpenSimplexNoise2D {
public:
    OpenSimplexNoise2D();
    OpenSimplexNoise2D(int64_t seed);
    // 2D Open Simplex Noise.
    float eval(float const x, float const y) const;

private:
    const float m_stretch2d;
    const float m_squish2d;

    const float m_norm2d;

    const long m_defaultSeed;

    std::default_random_engine m_engine;
    std::uniform_int_distribution<std::int64_t> distr;
    std::array<short, 256> m_perm;
    std::array<char, 16> m_gradients2d;
    float extrapolate(int xsb, int ysb, float dx, float dy) const;
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_RANDOM_OPEN_SIMPLEX_NOISE2D
