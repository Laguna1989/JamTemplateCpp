#ifndef JAMTEMPLATE_VECTOR_HPP_12345
#define JAMTEMPLATE_VECTOR_HPP_12345

#include <iosfwd>

namespace jt {

struct Vector2f {
    Vector2f();
    Vector2f(float x, float y);
    float x { 0.0f };
    float y { 0.0f };
};

struct Vector2u {
    Vector2u();
    Vector2u(unsigned int x, unsigned int y);
    unsigned int x { 0U };
    unsigned int y { 0U };
};

jt::Vector2f operator+(jt::Vector2f const& a, jt::Vector2f const& b);
jt::Vector2f operator-(jt::Vector2f const& a, jt::Vector2f const& b);

jt::Vector2f& operator+=(jt::Vector2f& lhs, jt::Vector2f const& rhs);
jt::Vector2f& operator-=(jt::Vector2f& lhs, jt::Vector2f const& rhs);

bool operator==(jt::Vector2f const& a, jt::Vector2f const& b);
bool operator!=(jt::Vector2f const& a, jt::Vector2f const& b);

jt::Vector2f operator*(float const f, jt::Vector2f const& v);
jt::Vector2f operator*(jt::Vector2f const& v, float const f);

jt::Vector2f operator/(jt::Vector2f const& v, float const f);

std::ostream& operator<<(std::ostream& os, const Vector2f& vec);

jt::Vector2u operator+(jt::Vector2u const& a, jt::Vector2u const& b);
jt::Vector2u operator-(jt::Vector2u const& a, jt::Vector2u const& b);

jt::Vector2u& operator+=(jt::Vector2u& lhs, jt::Vector2u const& other);

jt::Vector2u& operator-=(jt::Vector2u& lhs, jt::Vector2u const& other);

bool operator==(jt::Vector2u const& a, jt::Vector2u const& b);
bool operator!=(jt::Vector2u const& a, jt::Vector2u const& b);

std::ostream& operator<<(std::ostream& os, const Vector2u& vec);

} // namespace jt

#endif
