#include "palette_builder.hpp"
#include <color/color_factory.hpp>
#include <strutils.hpp>
#include <system_helper.hpp>
#include <fstream>

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
        auto col = jt::ColorFactory::fromRGB(r, g, b);
        colors.push_back(col);
    }

    return colors;
}

} // namespace

Palette PaletteBuilder::create() const { return Palette { m_colors }; }

PaletteBuilder& PaletteBuilder::addColorsFromGPL(std::string const& gplFileContent)
{
    auto const newColors = parseGPLImpl(gplFileContent);
    m_colors.insert(m_colors.end(), newColors.cbegin(), newColors.cend());
    return *this;
}

PaletteBuilder& PaletteBuilder::addGradientH(
    float hmin, float hmax, float s, float v, std::size_t steps)
{
    std::vector<jt::Color> colors;
    float const delta = (hmax - hmin) / steps;
    for (std::size_t step = 0U; step != steps; ++step) {
        auto const h = hmin + step * delta;
        colors.emplace_back(jt::ColorFactory::fromHSV(h, s, v));
    }
    m_colors.insert(m_colors.end(), colors.cbegin(), colors.cend());
    return *this;
}
PaletteBuilder& PaletteBuilder::addGradientS(
    float h, float smin, float smax, float v, std::size_t steps)
{
    std::vector<jt::Color> colors;
    float const delta = (smax - smin) / steps;
    for (std::size_t step = 0U; step != steps; ++step) {
        auto const s = smin + step * delta;
        colors.emplace_back(jt::ColorFactory::fromHSV(h, s, v));
    }
    m_colors.insert(m_colors.end(), colors.cbegin(), colors.cend());
    return *this;
}
PaletteBuilder& PaletteBuilder::addGradientV(
    float h, float s, float vmin, float vmax, std::size_t steps)
{
    std::vector<jt::Color> colors;
    float const delta = (vmax - vmin) / steps;
    for (std::size_t step = 0U; step != steps; ++step) {
        auto const v = vmin + step * delta;
        colors.emplace_back(jt::ColorFactory::fromHSV(h, s, v));
    }

    m_colors.insert(m_colors.end(), colors.cbegin(), colors.cend());
    return *this;
}
PaletteBuilder& PaletteBuilder::addColor(jt::Color const& col)
{
    m_colors.push_back(col);
    return *this;
}

PaletteBuilder& PaletteBuilder::addColorsFromPicture(Sprite& sprite)
{
    auto const w = static_cast<unsigned int>(sprite.getLocalBounds().width);
    auto const h = static_cast<unsigned int>(sprite.getLocalBounds().height);
    std::vector<jt::Color> colorsFromSprite;
    for (auto x = 0u; x != w; ++x) {
        for (auto y = 0u; y != h; ++y) {
            colorsFromSprite.push_back(sprite.getColorAtPixel(jt::Vector2u { x, y }));
        }
    }
    colorsFromSprite.erase(
        SystemHelper::remove_duplicates(colorsFromSprite.begin(), colorsFromSprite.end()),
        colorsFromSprite.end());
    m_colors.insert(m_colors.end(), colorsFromSprite.cbegin(), colorsFromSprite.cend());
    return *this;
}

PaletteBuilder& PaletteBuilder::makeUnique()
{
    m_colors.erase(
        SystemHelper::remove_duplicates(m_colors.begin(), m_colors.end()), m_colors.end());
    return *this;
}

} // namespace jt
