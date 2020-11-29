#include "Conversions.hpp"

namespace jt {
namespace Conversion {

jt::vector2 vec(b2Vec2 const& v) { return jt::vector2 { v.x, v.y }; }

b2Vec2 vec(jt::vector2 const& v) { return b2Vec2 { v.x(), v.y() }; }

jt::vector2 vec(tson::Vector2f const& v) { return jt::vector2 { v.x, v.y }; }

jt::vector2 vec(tson::Vector2i const& v)
{
    return jt::vector2 { static_cast<float>(v.x), static_cast<float>(v.y) };
}

} // namespace Conversion
} // namespace jt
