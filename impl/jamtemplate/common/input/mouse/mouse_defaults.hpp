#ifndef GUARD_JAMTEMPLATE_MOUSE_DEFAULTS_HPP
#define GUARD_JAMTEMPLATE_MOUSE_DEFAULTS_HPP

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
    MBMiddle,
    MBRight,
    ButtonCount ///< Keep last -- the total number of mouse button
};

std::vector<jt::MouseButtonCode> getAllMouseButtons();

} // namespace jt

#endif // GUARD_JAMTEMPLATE_MOUSE_DEFAULTS_HPP
