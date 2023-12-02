#include "mouse_defines.hpp"
#include <cstdint>

std::array<jt::MouseButtonCode, jt::MouseButtonCodeSize> jt::getAllMouseButtons()
{
    std::array<jt::MouseButtonCode, static_cast<std::size_t>(MouseButtonCode::ButtonCount)> values;
    for (std::uint32_t i = 0u; i != jt::MouseButtonCodeSize; ++i) {
        values.at(i) = static_cast<jt::MouseButtonCode>(i);
    }
    return values;
}
