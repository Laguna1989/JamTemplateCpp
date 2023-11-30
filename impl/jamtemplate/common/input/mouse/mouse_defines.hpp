#ifndef JAMTEMPLATE_MOUSE_DEFINES_HPP
#define JAMTEMPLATE_MOUSE_DEFINES_HPP

#include <array>
#include <cstdint>

namespace jt {
struct MousePosition {
    float window_x { 0.0f };
    float window_y { 0.0f };

    float screen_x { 0.0f };
    float screen_y { 0.0f };
};

enum class MouseButtonCode {
    MBLeft = 0,
    MBRight,
    MBMiddle,
    ButtonCount ///< Keep last -- the total number of mouse button
};

constexpr inline std::uint8_t MouseButtonCodeSize
    = static_cast<std::uint8_t>(MouseButtonCode::ButtonCount);

std::array<jt::MouseButtonCode, MouseButtonCodeSize> getAllMouseButtons();

} // namespace jt

#endif // JAMTEMPLATE_MOUSE_DEFINES_HPP
