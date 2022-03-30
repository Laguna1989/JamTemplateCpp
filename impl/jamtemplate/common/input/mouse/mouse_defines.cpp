#include "mouse_defines.hpp"
#include <cstdint>

std::vector<jt::MouseButtonCode> jt::getAllMouseButtons()
{
    auto const maxValue = static_cast<std::uint32_t>(jt::MouseButtonCode::ButtonCount);
    std::vector<jt::MouseButtonCode> values(maxValue, jt::MouseButtonCode::MBLeft);
    for (std::uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<jt::MouseButtonCode>(i);
    }
    return values;
}
