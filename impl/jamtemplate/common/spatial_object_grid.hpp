#ifndef JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
#define JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP

#include <memory>
#include <vector>

template <typename T>
class SpatialObjectGrid {
public:
    bool empty() const { return m_allObjects.empty(); };
    void push_back(std::weak_ptr<T> obj) {};

private:
    std::vector<std::weak_ptr<T>> m_allObjects;
};

#endif // JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
