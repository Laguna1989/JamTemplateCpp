#include "palette.hpp"

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

} // namespace jt
