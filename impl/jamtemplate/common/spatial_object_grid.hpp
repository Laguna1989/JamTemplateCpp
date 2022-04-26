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

CellIndex operator+(CellIndex const& a, CellIndex const& b)
{
    return CellIndex { a.x + b.x, a.y + b.y };
}

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
// TODO possibly add removing objects (also consider for ObjectGroup)
// TODO add moving objects
template <typename T, int cellSize>
class SpatialObjectGrid {
public:
    bool empty() const { return m_allObjects.empty(); };

    void push_back(std::weak_ptr<T> obj)
    {
        m_allObjects.push_back(obj);

        auto const lockedObj = obj.lock();
        auto const cellIndex = getCellIndex(lockedObj->getPosition());

        if (m_cells.count(cellIndex) == 0) {
            m_cells[cellIndex] = std::vector<std::weak_ptr<T>> {};
        }

        m_cells.at(cellIndex).push_back(obj);
    };

    std::vector<std::weak_ptr<T>> getObjectsAround(jt::Vector2f position, float distance) const
    {
        auto const cellIndex = getCellIndex(position);
        std::vector<std::weak_ptr<T>> objects {};
        auto const offsets = getOffsets(distance);
        for (auto const& offset : offsets) {
            auto const currentIndex = cellIndex + offset;

            if (m_cells.count(currentIndex) == 0) {
                continue;
            }

            objects.insert(
                objects.end(), m_cells.at(currentIndex).begin(), m_cells.at(currentIndex).end());
        }

        return objects;
    }

private:
    std::vector<std::weak_ptr<T>> m_allObjects;
    std::map<detail::CellIndex, std::vector<std::weak_ptr<T>>> m_cells;

    detail::CellIndex getCellIndex(jt::Vector2f const& position) const
    {
        return detail::CellIndex { static_cast<int>(position.x) / cellSize,
            static_cast<int>(position.y) / cellSize };
    }

    std::vector<detail::CellIndex> getOffsets(float distance) const
    {
        std::vector<detail::CellIndex> offsets;
        int const distanceInCells = (static_cast<int>(distance) / cellSize) + 1;

        for (auto x = -distanceInCells; x != distanceInCells + 1; ++x) {
            for (auto y = -distanceInCells; y != distanceInCells + 1; ++y) {
                offsets.push_back({ x, y });
            }
        }

        //        // TODO actually use distance
        //        // clang-format off
        //        return std::vector<detail::CellIndex> {
        //            { -1, -1 }, { -1, 0 }, { -1, 1 },
        //            { 0, -1 }, { 0, 0 }, { 0, 1 },
        //            { 1, -1 }, { 1, 0 }, { 1, 1 },
        //        };
        //        // clang-format on

        return offsets;
    }
};

} // namespace jt

#endif // JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
