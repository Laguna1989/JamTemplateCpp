#include "key_codes.hpp"
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

std::vector<jt::MouseButtonCode> jt::getAllButtons()
{
    auto const maxValue = static_cast<std::uint32_t>(jt::MouseButtonCode::ButtonCount);
    std::vector<jt::MouseButtonCode> values(maxValue, jt::MouseButtonCode::MBLeft);
    for (std::uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<jt::MouseButtonCode>(i);
    }
    return values;
}

std::vector<jt::GamepadAxisCode> jt::getAllAxis()
{
    auto const maxValue = static_cast<std::uint32_t>(jt::GamepadAxisCode::AxisCount);
    std::vector<jt::GamepadAxisCode> values(maxValue, jt::GamepadAxisCode::ALeft);
    for (std::uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<jt::GamepadAxisCode>(i);
    }
    return values;
}
