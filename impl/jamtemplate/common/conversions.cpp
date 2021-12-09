#include "conversions.hpp"

namespace jt {
namespace Conversion {

jt::Vector2f vec(b2Vec2 const& v) { return jt::Vector2f { v.x, v.y }; }

b2Vec2 vec(jt::Vector2f const& v) { return b2Vec2 { v.x, v.y }; }

jt::Vector2f vec(tson::Vector2f const& v) { return jt::Vector2f { v.x, v.y }; }

jt::Vector2f vec(tson::Vector2i const& v)
{
    return jt::Vector2f { static_cast<float>(v.x), static_cast<float>(v.y) };
}

} // namespace Conversion
} // namespace jt
