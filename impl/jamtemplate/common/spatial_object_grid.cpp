#include "spatial_object_grid.hpp"

bool jt::detail::operator<(CellIndex const& a, CellIndex const& b)
{
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}