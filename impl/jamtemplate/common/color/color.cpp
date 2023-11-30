#include "color.hpp"
#include <ostream>

std::ostream& jt::operator<<(std::ostream& os, jt::Color const& color)
{
    os << "( " << static_cast<int>(color.r) << ", " << static_cast<int>(color.g) << ", "
       << static_cast<int>(color.b) << ", " << static_cast<int>(color.a) << " )";
    return os;
}
