#ifndef GUARD_JAMTEMPLATE_RECT_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_RECT_GUARD_HPP_12345

namespace jt {

struct Rectf {
    float left { 0.0f };
    float top { 0.0f };
    float width { 0.0f };
    float height { 0.0f };
};

struct Recti {
    int left { 0 };
    int top { 0 };
    int width { 0 };
    int height { 0 };
};

bool operator==(jt::Rectf const& a, jt::Rectf const& b);
bool operator!=(jt::Rectf const& a, jt::Rectf const& b);

bool operator==(jt::Recti const& a, jt::Recti const& b);
bool operator!=(jt::Recti const& a, jt::Recti const& b);

} // namespace jt
#endif
