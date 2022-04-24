#ifndef JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
#define JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP

#include "vector.hpp"
#include <map>
#include <memory>
#include <vector>

// TODO check for possible refactoring

namespace jt {

namespace detail {
struct CellIndex {
    int x { 0 };
    int y { 0 };
};

bool operator==(CellIndex const& a, CellIndex const& b) { return a.x == b.x && a.y == b.y; }
bool operator!=(CellIndex const& a, CellIndex const& b) { return !(a == b); }

bool operator<(CellIndex const& a, CellIndex const& b)
{
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

} // namespace detail

// TODO inherit from jt::GameObject
// TODO implement update function and disposal of dead objects
// TODO re-sort objects into cells
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
        // TODO actually use distance

        auto const cellIndices = getCellIndices(position);
        std::vector<std::weak_ptr<T>> objects {};
        auto const offsets = getOffsets(distance);
        for (auto const& offset : offsets) {
            detail::CellIndex currentIndices { cellIndices.x + offset.x, cellIndices.y + offset.y };

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
    std::map<detail::CellIndex, std::vector<std::weak_ptr<T>>> m_cells;

    detail::CellIndex getCellIndices(jt::Vector2f const& position) const
    {
        return detail::CellIndex { static_cast<int>(position.x) / gridSize,
            static_cast<int>(position.y) / gridSize };
    }

    std::vector<detail::CellIndex> getOffsets(float distance) const
    {
        // clang-format off
        return std::vector<detail::CellIndex> {
            { -1, -1 }, { -1, 0 }, { -1, 1 },
            { 0, -1 }, { 0, 0 }, { 0, 1 },
            { 1, -1 }, { 1, 0 }, { 1, 1 },
        };
        // clang-format on
    }
};

} // namespace jt

#endif // JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
