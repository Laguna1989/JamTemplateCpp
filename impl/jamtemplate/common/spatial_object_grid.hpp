#ifndef JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
#define JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP

template <typename T>
class SpatialObjectGrid {
public:
    bool empty() const;
};

template <typename T>
bool SpatialObjectGrid<T>::empty() const
{
    return false;
}

#endif // JAMTEMPLATE_SPATIAL_OBJECT_GRID_HPP
