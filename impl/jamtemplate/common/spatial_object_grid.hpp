#ifndef JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
#define JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP

#include "vector.hpp"
#include <map>
#include <memory>
#include <vector>

namespace jt {
template <typename T, int gridSize>
class SpatialObjectGrid {
public:
    bool empty() const { return m_allObjects.empty(); };

    void push_back(std::weak_ptr<T> obj)
    {
        m_allObjects.push_back(obj);

        auto const lockedObj = obj.lock();
        auto const cellIndices = getCellIndices(lockedObj->getPosition());

        if (m_cells.count(cellIndices) == 0) {
            m_cells[cellIndices] = std::vector<std::weak_ptr<T>> {};
        }

        m_cells.at(cellIndices).push_back(obj);
    };

    std::vector<std::weak_ptr<T>> getObjectsAround(jt::Vector2f position, float distance) const
    {
        auto const cellIndices = getCellIndices(position);
        if (m_cells.count(cellIndices) == 0) {
            return std::vector<std::weak_ptr<T>> {};
        }
        return m_cells.at(cellIndices);
    }

private:
    std::vector<std::weak_ptr<T>> m_allObjects;
    std::map<std::pair<int, int>, std::vector<std::weak_ptr<T>>> m_cells;

    std::pair<int, int> getCellIndices(jt::Vector2f const& position) const
    {
        return std::pair<int, int> { static_cast<int>(position.x) / gridSize,
            static_cast<int>(position.y) / gridSize };
    }
};

} // namespace jt

#endif // JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
