#include "keyboard_defines.hpp"

std::vector<jt::KeyCode> jt::getAllKeys()
{
    std::vector<jt::KeyCode> values(KeyCode::_size(), jt::KeyCode::A);
    for (auto k : KeyCode::_values()) {
        values.at(k) = k;
    }
    return values;
}
