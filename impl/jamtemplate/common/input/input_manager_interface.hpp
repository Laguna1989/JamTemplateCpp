#pragma once

#include <input/input_get_interface.hpp>
#include <input/input_set_interface.hpp>
#include <memory>

namespace jt {

class InputManagerInterface : public InputSetInterface, public InputGetInterface { };

} // namespace jt
