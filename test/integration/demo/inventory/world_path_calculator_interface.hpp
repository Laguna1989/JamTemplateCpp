#ifndef ALAKAJAM14_WORLD_PATH_CALCULATOR_INTERFACE_HPP
#define ALAKAJAM14_WORLD_PATH_CALCULATOR_INTERFACE_HPP

#include <pathfinder/node_interface.hpp>
#include <memory>
#include <vector>

class WorldPathCalculatorInterface {
public:
    virtual ~WorldPathCalculatorInterface() = default;
    virtual std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> calculatePath(
        jt::Vector2f const& startPos, jt::Vector2f const& endPos)
        = 0;
};

#endif // ALAKAJAM14_WORLD_PATH_CALCULATOR_INTERFACE_HPP
