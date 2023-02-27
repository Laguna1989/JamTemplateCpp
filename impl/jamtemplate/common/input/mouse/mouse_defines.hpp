#ifndef JAMTEMPLATE_MOUSE_DEFINES_HPP
#define JAMTEMPLATE_MOUSE_DEFINES_HPP

#include <vector>

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

std::vector<jt::MouseButtonCode> getAllMouseButtons();

} // namespace jt

#endif // JAMTEMPLATE_MOUSE_DEFINES_HPP
