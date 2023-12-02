#include "rect.hpp"
#include <ostream>

std::ostream& jt::operator<<(std::ostream& os, jt::Rectf const& rect)
{
    return os << "[ (" << rect.left << ", " << rect.top << "), (" << rect.width << ", "
              << rect.height << ") ]";
}

std::ostream& jt::operator<<(std::ostream& os, jt::Recti const& rect)
{
    return os << "[ (" << rect.left << ", " << rect.top << "), (" << rect.width << ", "
              << rect.height << ") ]";
}
