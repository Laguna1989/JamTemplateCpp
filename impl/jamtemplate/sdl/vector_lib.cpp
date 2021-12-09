#include "vector_lib.hpp"

SDL_Point toLib(jt::Vector2f const& vec) { return SDL_Point { vec.x, vec.y }; }
jt::Vector2f fromLib(SDL_Point const& vec) { return jt::Vector2f { vec.x, vec.y }; }

SDL_Point toLib(jt::Vector2u const& vec)
{
    return SDL_Point { static_cast<int>(vec.x), static_cast<int>(vec.y) };
}
jt::Vector2u fromLib(SDL_Point const& vec)
{
    return jt::Vector2u { static_cast<int>(vec.x), static_cast<int>(vec.y) };
}

namespace jt {
}
