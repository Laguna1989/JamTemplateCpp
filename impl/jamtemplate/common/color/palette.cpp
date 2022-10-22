#include "palette.hpp"
#include <strutils.hpp>

jt::Palette::Palette(std::vector<jt::Color> const& colors)
    : m_colors { colors }
{
}

std::size_t jt::Palette::size() const { return m_colors.size(); }

bool jt::Palette::empty() const { return m_colors.empty(); }

jt::Color const& jt::Palette::getColor(std::size_t idx) const { return m_colors.at(idx); }
