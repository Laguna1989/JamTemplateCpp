#ifndef GUARD_JAMTEMPLATE_BASIC_ACTION_COMMANDS_HPP
#define GUARD_JAMTEMPLATE_BASIC_ACTION_COMMANDS_HPP

#include <memory>

namespace jt {
class GameBase;

void addBasicActionCommands(std::shared_ptr<jt::GameBase>& game);

} // namespace jt
#endif // GUARD_JAMTEMPLATE_BASIC_ACTION_COMMANDS_HPP
