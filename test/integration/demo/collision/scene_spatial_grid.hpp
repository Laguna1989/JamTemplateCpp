#ifndef DEMO_SCENE_SPATIAL_GRID_HPP
#define DEMO_SCENE_SPATIAL_GRID_HPP

#include <game_object.hpp>
#include <shape.hpp>
#include <spatial_object_grid.hpp>
#include <text.hpp>
#include <vector.hpp>
#include <memory>
#include <vector>

struct GridDot {
    jt::Vector2f position;
    jt::Vector2f velocity;
    jt::Vector2f getPosition() const { return position; }
};

/// Many moving dots stored in a jt::SpatialObjectGrid. Only the dots in the cells around the
/// mouse are checked for the exact distance.
class SceneSpatialGrid : public jt::GameObject {
public:
    static constexpr int cellSize { 32 };

    std::string getName() const override;

private:
    std::shared_ptr<jt::SpatialObjectGrid<GridDot, cellSize>> m_grid { nullptr };
    std::vector<std::shared_ptr<GridDot>> m_dots {};

    std::vector<std::shared_ptr<GridDot>> m_candidates {};
    std::vector<std::shared_ptr<GridDot>> m_hits {};
    float m_queryRadius { 40.0f };

    std::shared_ptr<jt::Shape> m_dotShape { nullptr };
    std::shared_ptr<jt::Shape> m_cellShape { nullptr };
    std::shared_ptr<jt::Shape> m_radiusShape { nullptr };
    std::shared_ptr<jt::Text> m_info { nullptr };

    void doCreate() override;
    void doUpdate(float elapsed) override;
    void doDraw() const override;

    void moveDots(float elapsed);
    void queryAroundMouse();
    void drawQueriedCells() const;
    void drawDots(std::vector<std::shared_ptr<GridDot>> const& dots, jt::Color const& color) const;
};

#endif // DEMO_SCENE_SPATIAL_GRID_HPP
