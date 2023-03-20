
#include "world_path_calculator.hpp"
#include <pathfinder/pathfinder.hpp>

std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> WorldPathCalculator::calculatePath(
    jt::Vector2f const& /*startPos*/, jt::Vector2f const& /*endPos*/)
{
    //    auto l = m_level.lock();
    //    auto const tileForStart = l->getPathfinderNodeAtPosition(startPos);
    //    auto const tileForEnd = l->getPathfinderNodeAtPosition(endPos);
    //    return jt::pathfinder::calculatePath(tileForStart, tileForEnd);
    return {};
}
