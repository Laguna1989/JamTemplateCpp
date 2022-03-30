#include "keyboard_defaults.hpp"
#include <cstdint>

std::vector<jt::KeyCode> jt::getAllKeys()
{
    auto const maxValue = static_cast<std::uint32_t>(jt::KeyCode::KeyCount);
    std::vector<jt::KeyCode> values(maxValue, jt::KeyCode::A);
    for (std::uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<jt::KeyCode>(i);
    }
    return values;
}
