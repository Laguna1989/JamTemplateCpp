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
    void push_back(std::weak_ptr<T> obj) { m_allObjects.push_back(obj); };

    std::vector<std::weak_ptr<T>> getObjectsAround(jt::Vector2f position, float distance) const
    {
        return std::vector<std::weak_ptr<T>> {};
    }

private:
    std::vector<std::weak_ptr<T>> m_allObjects;
    std::map<std::pair<int, int>, std::vector<std::weak_ptr<T>>> m_grids;
};

} // namespace jt

#endif // JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
