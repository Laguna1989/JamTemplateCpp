#ifndef JAMTEMPLATE_PALETTE_HPP
#define JAMTEMPLATE_PALETTE_HPP

#include <color/color.hpp>
#include <cstddef>
#include <vector>

namespace jt {
class Palette {
public:
    Palette() = default;
    Palette(std::vector<jt::Color> const& colors);

    static Palette createGradientH(float hmin, float hmax, float s, float v, std::size_t steps);
    static Palette createGradientS(float h, float smin, float smax, float v, std::size_t steps);
    static Palette createGradientV(float h, float s, float vmin, float vmax, std::size_t steps);

    std::size_t size() const;
    bool empty() const;

    [[nodiscard]] Palette addColor(jt::Color col) const;
    jt::Color const& getColor(std::size_t idx) const;

    static Palette parseGPL(std::string const& gplFileContent);
    static Palette parseGPLFromFile(std::string const& fileName);

private:
    std::vector<jt::Color> m_colors;
};

} // namespace jt

#endif // JAMTEMPLATE_PALETTE_HPP
