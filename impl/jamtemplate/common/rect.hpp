#ifndef JAMTEMPLATE_RECT_HPP_12345
#define JAMTEMPLATE_RECT_HPP_12345

#include <iosfwd>

namespace jt {

struct Rectf {
    Rectf();
    Rectf(float l, float t, float w, float h);
    float left { 0.0f };
    float top { 0.0f };
    float width { 0.0f };
    float height { 0.0f };
};

struct Recti {
    Recti();
    Recti(int l, int t, int w, int h);

    int left { 0 };
    int top { 0 };
    int width { 0 };
    int height { 0 };
};

bool operator==(jt::Rectf const& a, jt::Rectf const& b);
bool operator!=(jt::Rectf const& a, jt::Rectf const& b);

bool operator==(jt::Recti const& a, jt::Recti const& b);
bool operator!=(jt::Recti const& a, jt::Recti const& b);

std::ostream& operator<<(std::ostream& os, Rectf const& rect);
} // namespace jt
#endif
