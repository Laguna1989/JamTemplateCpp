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

        std::vector<std::weak_ptr<T>> objects { m_cells.at(cellIndices) };
        auto const offsets = getOffsets(distance);
        for (auto const& offset : offsets) {
            std::pair<int, int> currentIndices { cellIndices.first + offset.first,
                cellIndices.second + offset.second };

            if (m_cells.count(currentIndices) == 0) {
                continue;
            }

            objects.insert(objects.end(), m_cells.at(currentIndices).begin(),
                m_cells.at(currentIndices).end());
        }

        return objects;
    }

private:
    std::vector<std::weak_ptr<T>> m_allObjects;
    std::map<std::pair<int, int>, std::vector<std::weak_ptr<T>>> m_cells;

    std::pair<int, int> getCellIndices(jt::Vector2f const& position) const
    {
        return std::pair<int, int> { static_cast<int>(position.x) / gridSize,
            static_cast<int>(position.y) / gridSize };
    }

    std::vector<std::pair<int, int>> getOffsets(float distance) const
    {
        // clang-format off
        return std::vector<std::pair<int, int>> {
            { -1, -1 }, { -1, 0 }, { -1, 1 },
            { 0, -1 }, { 0, 1 },
            { 1, -1 }, { 1, 0 }, { 1, 1 },
        };
        // clang-format on
    }
};

} // namespace jt

#endif // JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
