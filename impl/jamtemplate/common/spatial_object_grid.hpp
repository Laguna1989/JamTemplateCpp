#ifndef JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
#define JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP

#include <game_object.hpp>
#include <system_helper.hpp>
#include <vector.hpp>
#include <map>
#include <memory>
#include <vector>

namespace jt {

namespace detail {
struct CellIndex {
    int x { 0 };
    int y { 0 };
    constexpr bool operator==(CellIndex const& other) const = default;
    constexpr bool operator!=(CellIndex const& other) const = default;
};

constexpr CellIndex operator+(CellIndex const& a, CellIndex const& b)
{
    return CellIndex { a.x + b.x, a.y + b.y };
}

bool operator<(CellIndex const& a, CellIndex const& b);

} // namespace detail

// TODO possibly add removing objects (also consider for ObjectGroup)
template <typename T, int cellSize>
class SpatialObjectGrid : public jt::GameObject {
public:
    bool empty() const noexcept { return m_allObjects.empty(); };

    void push_back(std::weak_ptr<T> obj)
    {
        m_allObjects.push_back(obj);

        auto const lockedObject = obj.lock();
        auto const cellIndex = getCellIndex(lockedObject->getPosition());

        if (!m_cells.contains(cellIndex)) {
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

            if (!m_cells.contains(currentIndex)) {
                continue;
            }

            objects.insert(
                objects.end(), m_cells.at(currentIndex).begin(), m_cells.at(currentIndex).end());
        }

        return objects;
    }

    void doUpdate(float const /*elapsed*/) override
    {
        std::unordered_set<std::shared_ptr<T>> objectsToReplace;

        for (auto& kvp : m_cells) {
            std::vector<std::shared_ptr<T>> currentObjects {};
            std::vector<std::shared_ptr<T>> objectsToRemove {};

            for (auto& object : kvp.second) {
                auto const lockedObject = object.lock();
                if (lockedObject == nullptr) {
                    continue;
                }
                currentObjects.push_back(lockedObject);
                auto const objectPosition = lockedObject->getPosition();

                auto const oldIndex = kvp.first;
                auto const newIndex = getCellIndex(objectPosition);

                if (oldIndex == newIndex) {
                    continue;
                }

                objectsToRemove.push_back(lockedObject);
            }
            jt::SystemHelper::remove_intersection(currentObjects, objectsToRemove);

            objectsToReplace.insert(objectsToRemove.begin(), objectsToRemove.end());
            kvp.second = jt::SystemHelper::to_weak_pointers(currentObjects);
        }

        for (auto const& object : objectsToReplace) {
            push_back(object);
        }
    }

private:
    std::vector<std::weak_ptr<T>> m_allObjects;
    std::map<detail::CellIndex, std::vector<std::weak_ptr<T>>> m_cells;

    detail::CellIndex getCellIndex(jt::Vector2f const& position) const
    {
        return detail::CellIndex { static_cast<int>(std::floor(position.x / cellSize)),
            static_cast<int>(std::floor(position.y / cellSize)) };
    }

    std::vector<detail::CellIndex> getOffsets(float distance) const
    {
        int const distanceInCells { static_cast<int>(std::ceil(distance / cellSize)) };
        std::vector<detail::CellIndex> offsets;

        for (auto x = -distanceInCells; x != distanceInCells + 1; ++x) {
            for (auto y = -distanceInCells; y != distanceInCells + 1; ++y) {
                offsets.push_back({ x, y });
            }
        }

        return offsets;
    }
};

} // namespace jt

#endif // JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
