#ifndef JAMTEMPLATE_PATHFINDINDER_HPP
#define JAMTEMPLATE_PATHFINDINDER_HPP

#include <pathfinder/node_interface.hpp>
#include <memory>
#include <vector>

namespace jt {
namespace pathfinder {

using NodeT = std::shared_ptr<NodeInterface>;

std::vector<NodeT> calculatePath(NodeT const& start, NodeT const& end);

} // namespace pathfinder
} // namespace jt

#endif // JAMTEMPLATE_PATHFINDINDER_HPP
