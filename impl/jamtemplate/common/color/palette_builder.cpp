
#include "palette_builder.hpp"
#include <color/color_builder.hpp>
#include <strutils.hpp>
#include <fstream>
#include <sstream>

namespace jt {

namespace {
std::vector<jt::Color> parseGPLImpl(std::string const& gplFileConent)
{
    std::istringstream ss { gplFileConent };
    std::string line;
    // ignore first line
    std::getline(ss, line);

    std::vector<jt::Color> colors {};
    while (std::getline(ss, line)) {
        if (line.empty()) {
            continue;
        }
        strutil::trim(line);
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
        auto col = jt::ColorBuilder::fromRGB(r, g, b);
        colors.push_back(col);
    }

    return colors;
}

} // namespace

Palette PaletteBuilder::create() const { return Palette { m_colors }; }

PaletteBuilder& PaletteBuilder::parseGPL(std::string const& gplFileContent)
{
    auto const newColors = parseGPLImpl(gplFileContent);
    m_colors.insert(m_colors.end(), newColors.cbegin(), newColors.cend());
    return *this;
}

PaletteBuilder& PaletteBuilder::createGradientH(
    float hmin, float hmax, float s, float v, std::size_t steps)
{
    std::vector<jt::Color> colors;
    float const delta = (hmax - hmin) / steps;
    for (std::size_t step = 0U; step != steps; ++step) {
        auto const h = hmin + step * delta;
        colors.emplace_back(jt::ColorBuilder::fromHSV(h, s, v));
    }
    m_colors.insert(m_colors.end(), colors.cbegin(), colors.cend());
    return *this;
}
PaletteBuilder& PaletteBuilder::createGradientS(
    float h, float smin, float smax, float v, std::size_t steps)
{
    std::vector<jt::Color> colors;
    float const delta = (smax - smin) / steps;
    for (std::size_t step = 0U; step != steps; ++step) {
        auto const s = smin + step * delta;
        colors.emplace_back(jt::ColorBuilder::fromHSV(h, s, v));
    }
    m_colors.insert(m_colors.end(), colors.cbegin(), colors.cend());
    return *this;
}
PaletteBuilder& PaletteBuilder::createGradientV(
    float h, float s, float vmin, float vmax, std::size_t steps)
{
    std::vector<jt::Color> colors;
    float const delta = (vmax - vmin) / steps;
    for (std::size_t step = 0U; step != steps; ++step) {
        auto const v = vmin + step * delta;
        colors.emplace_back(jt::ColorBuilder::fromHSV(h, s, v));
    }

    m_colors.insert(m_colors.end(), colors.cbegin(), colors.cend());
    return *this;
}
PaletteBuilder& PaletteBuilder::addColor(jt::Color const& col)
{
    m_colors.push_back(col);
    return *this;
}
} // namespace jt