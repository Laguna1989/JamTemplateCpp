/**
  Open Simple Noise for C++

  Port to C++ from https://gist.github.com/KdotJPG/b1270127455a94ac5d19
  by Rickard Lundberg, 2019.
  see https://github.com/deerel/OpenSimplexNoise
*/

#ifndef GUARD_JAMTEMPLATE_RANDOM_OPEN_SIMPLEX_NOISE3D
#define GUARD_JAMTEMPLATE_RANDOM_OPEN_SIMPLEX_NOISE3D

#include <array>
#include <cstdint>
#include <random>

namespace jt {

class OpenSimplexNoise3D {
public:
    OpenSimplexNoise3D();
    OpenSimplexNoise3D(int64_t seed);

    // 3D Open Simplex Noise.
    float eval(float x, float y, float z) const;

private:
    const float m_stretch3d;
    const float m_squish3d;

    const float m_norm3d;

    std::default_random_engine m_engine;
    std::uniform_int_distribution<std::int64_t> distr;

    std::array<short, 256> m_perm;
    std::array<short, 256> m_permGradIndex3d;
    std::array<char, 72> m_gradients3d;
    float extrapolate(int xsb, int ysb, int zsb, float dx, float dy, float dz) const;
};
} // namespace jt

#endif
