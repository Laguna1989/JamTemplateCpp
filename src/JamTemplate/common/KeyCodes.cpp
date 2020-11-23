#include "KeyCodes.hpp"

namespace jt {
std::vector<jt::KeyCode> getAllKeys()
{
    auto const maxValue = static_cast<uint32_t>(jt::KeyCode::KeyCount);
    std::vector<jt::KeyCode> values(maxValue, jt::KeyCode::A);
    for (uint32_t i = 0U; i != maxValue; ++i) {
        values.at(i) = static_cast<jt::KeyCode>(i);
    }
    return values;
}

} // namespace jt