
#ifndef JAMTEMPLATE_WORLD_PATH_CALCULATOR_HPP
#define JAMTEMPLATE_WORLD_PATH_CALCULATOR_HPP

#include <inventory/world_path_calculator_interface.hpp>

class WorldPathCalculator : public WorldPathCalculatorInterface {
public:
    std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> calculatePath(
        jt::Vector2f const& startPos, jt::Vector2f const& endPos) override;

private:
    //    std::weak_ptr<inventory::Level> m_level;
};

#endif // JAMTEMPLATE_WORLD_PATH_CALCULATOR_HPP
