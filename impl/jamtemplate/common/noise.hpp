#ifndef GUARD_JAMTEMPLATE_NOISE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_NOISE_HPP_INCLUDEGUARD

#include "lerp.hpp"
#include "random/random.hpp"
#include <iostream>
#include <vector>

namespace jt {
namespace Noise {

class ValueNoise1D {
public:
    explicit ValueNoise1D(size_t samplePoints)
    {
        m_sampleValues.resize(samplePoints, 0);
        // fill vector with random points between 0 and 1
        for (auto& s : m_sampleValues) {
            s = Random::getFloat(0, 1);
        }
    }

    /// x is expected to be between 0 and 1, periodic boundaries otherwise
    /// returns values between 0 and 1
    float get(float x)
    {
        if (m_sampleValues.empty())
            throw std::exception();

        // make x fit between 0 and 1
        if (x > 1) {
            float delta = std::floor(x);
            x -= delta;
        }
        if (x < 0) {
            float delta = std::floor(x);
            x -= delta;
        }
        if (x == 0) {
            return m_sampleValues.at(0);
        }
        if (x == 1) {
            return m_sampleValues.at(m_sampleValues.size() - 1);
        }

        size_t lowIdx = static_cast<size_t>(x * (m_sampleValues.size()));
        if (lowIdx == m_sampleValues.size()) {
            return m_sampleValues.at(m_sampleValues.size());
        }
        float lowValue = m_sampleValues.at(lowIdx);

        size_t highIdx = static_cast<size_t>(x * m_sampleValues.size() + 1);
        float highValue = (highIdx == m_sampleValues.size()) ? m_sampleValues.at(0)
                                                             : m_sampleValues.at(highIdx);

        float delta = 1.0f / m_sampleValues.size();
        x -= delta * lowIdx;

        if (x == 0) {
            return lowValue;
        } else if (x >= delta * 0.99) {
            return highValue;
        } else {
            // interpolation required here
            x /= delta; // x between 0 and 1 now

            return Lerp::cosine<float>(lowValue, highValue, x);
        }
        return 0;
    }

private:
    std::vector<float> m_sampleValues {};
};

} // namespace Noise
} // namespace jt
#endif
