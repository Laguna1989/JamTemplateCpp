#pragma once

#include <memory>

namespace jt {
class GameBase;

void addBasicActionCommands(std::shared_ptr<jt::GameBase> game);

} // namespace jt
