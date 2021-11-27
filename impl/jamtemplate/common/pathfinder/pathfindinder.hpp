#ifndef GUARD_JAMTEMPLATE_PATHFINDINDER_HPP
#define GUARD_JAMTEMPLATE_PATHFINDINDER_HPP

#include "node_interface.hpp"
#include <memory>
#include <vector>

namespace jt {
namespace pathfinder {

using NodeT = std::shared_ptr<NodeInterface>;

std::vector<NodeT> calculatePath(NodeT start, NodeT end);

} // namespace pathfinder
} // namespace jt

#endif // GUARD_JAMTEMPLATE_PATHFINDINDER_HPP
