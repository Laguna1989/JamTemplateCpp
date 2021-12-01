#ifndef GUARD_JAMTEMPLATE_PALETTE_HPP
#define GUARD_JAMTEMPLATE_PALETTE_HPP

#include "color.hpp"
#include <vector>

namespace jt {
class Palette {
public:
    Palette() = default;
    Palette(std::vector<jt::Color> const& colors);
    std::size_t size() const;
    bool empty() const;

    [[nodiscard]] Palette addColor(jt::Color col) const;
    jt::Color const& getColor(std::size_t idx) const;

private:
    std::vector<jt::Color> m_colors;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_PALETTE_HPP
