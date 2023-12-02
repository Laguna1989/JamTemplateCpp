#include "conversions.hpp"

jt::Vector2f jt::Conversion::vec(b2Vec2 const& v) noexcept { return jt::Vector2f { v.x, v.y }; }

b2Vec2 jt::Conversion::vec(jt::Vector2f const& v) noexcept { return b2Vec2 { v.x, v.y }; }

jt::Vector2f jt::Conversion::vec(tson::Vector2f const& v) noexcept
{
    return jt::Vector2f { v.x, v.y };
}

jt::Vector2f jt::Conversion::vec(tson::Vector2i const& v) noexcept
{
    return jt::Vector2f { static_cast<float>(v.x), static_cast<float>(v.y) };
}
