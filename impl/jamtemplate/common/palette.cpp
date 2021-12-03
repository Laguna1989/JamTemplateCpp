#include "palette.hpp"
#include "strutils.hpp"
#include <sstream>

namespace jt {
Palette::Palette(std::vector<jt::Color> const& colors)
    : m_colors { colors }
{
}

std::size_t Palette::size() const { return m_colors.size(); }
bool Palette::empty() const { return m_colors.empty(); }
jt::Color const& Palette::getColor(std::size_t idx) const { return m_colors.at(idx); }
Palette Palette::addColor(jt::Color col) const
{
    std::vector<jt::Color> newColors { m_colors };
    newColors.push_back(col);
    return Palette { newColors };
}
Palette Palette::createGradientH(float hmin, float hmax, float s, float v, std::size_t steps)
{
    std::vector<jt::Color> colors;
    float const delta = (hmax - hmin) / steps;
    for (std::size_t step = 0U; step != steps; ++step) {
        auto const h = hmin + step * delta;
        colors.emplace_back(jt::MakeColor::FromHSV(h, s, v));
    }
    return Palette { colors };
}

Palette Palette::createGradientS(float h, float smin, float smax, float v, std::size_t steps)
{
    std::vector<jt::Color> colors;
    float const delta = (smax - smin) / steps;
    for (std::size_t step = 0U; step != steps; ++step) {
        auto const s = smin + step * delta;
        colors.emplace_back(jt::MakeColor::FromHSV(h, s, v));
    }
    return Palette { colors };
}
Palette Palette::createGradientV(float h, float s, float vmin, float vmax, std::size_t steps)
{
    std::vector<jt::Color> colors;
    float const delta = (vmax - vmin) / steps;
    for (std::size_t step = 0U; step != steps; ++step) {
        auto const v = vmin + step * delta;
        colors.emplace_back(jt::MakeColor::FromHSV(h, s, v));
    }
    return Palette { colors };
}

namespace {
std::vector<jt::Color> parseGPLImpl(std::string const& input)
{
    std::istringstream ss { input };
    std::string line;
    // ignore first line
    std::getline(ss, line);

    std::vector<jt::Color> colors {};
    while (std::getline(ss, line)) {
        strutil::trim(line);
        if (line.empty()) {
            continue;
        }
        if (line.at(0) == '#') {
            continue;
        }
        strutil::replace_all(line, "\t", " ");
        auto const ssv = strutil::split(line, " ");
        if (ssv.size() != 4) {
            throw std::invalid_argument { "line does not adhere to gpl spec" };
        }
        std::uint8_t const r = static_cast<std::uint8_t>(strutil::parse_string<int>(ssv[0]));
        std::uint8_t const g = static_cast<std::uint8_t>(strutil::parse_string<int>(ssv[1]));
        std::uint8_t const b = static_cast<std::uint8_t>(strutil::parse_string<int>(ssv[2]));
        auto col = jt::MakeColor::FromRGB(r, g, b);
        colors.push_back(col);
    }

    return colors;
}

} // namespace

Palette Palette::parseGPL(std::string const& input) { return Palette { parseGPLImpl(input) }; }

} // namespace jt
