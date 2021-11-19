#ifndef MYAWESOMEGAME_COLOR_HELPERS_HPP
#define MYAWESOMEGAME_COLOR_HELPERS_HPP

#include <cstdint>
#include <string>
#include <tuple>

namespace jt {
namespace ColorHelpers {
///
/// \param h hue value [0-360]
/// \param s saturation value [0-100]
/// \param v value value [0-100]
/// \return rgb tuple, each [0-255]
std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> hsv2rgb(float h, float s, float v);

} // namespace ColorHelpers
} // namespace jt
#endif // MYAWESOMEGAME_COLOR_HELPERS_HPP
