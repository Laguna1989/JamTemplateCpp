#ifndef JAMTEMPLATE_INPUTHELPER_HPP
#define JAMTEMPLATE_INPUTHELPER_HPP

#include <map>

namespace jt {
namespace inputhelper {

// common template function which works for mouse buttons, keyboard keys and gamepad buttons.
template <typename CheckFuncArg, typename KeyTypeJT>
void updateValues(std::map<KeyTypeJT, bool>& pressed, std::map<KeyTypeJT, bool>& released,
    std::map<KeyTypeJT, bool>& justPressed, std::map<KeyTypeJT, bool>& justReleased,
    CheckFuncArg const& check)
{
    for (auto const& kvp : pressed) {
        auto const key = kvp.first;
        auto const keyValue = check(key);
        if (keyValue) {
            justPressed[key] = (pressed[key] == false);
            justReleased[key] = false;
        } else {
            justReleased[key] = (pressed[key] == true);
            justPressed[key] = false;
        }
        pressed[key] = keyValue;
        released[key] = !keyValue;
    }
}
} // namespace inputhelper
} // namespace jt

#endif // !JAMTEMPLATE_INPUTHELPER_HPP
