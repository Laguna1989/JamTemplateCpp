#ifndef JAMTEMPLATE_BASIC_ACTION_COMMANDS_HPP
#define JAMTEMPLATE_BASIC_ACTION_COMMANDS_HPP

#include <memory>

namespace jt {
class GameBase;

void addBasicActionCommands(std::shared_ptr<jt::GameBase> game);

} // namespace jt
#endif // JAMTEMPLATE_BASIC_ACTION_COMMANDS_HPP
