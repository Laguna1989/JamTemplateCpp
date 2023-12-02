#ifndef JAMTEMPLATE_BOUNCE_HPP
#define JAMTEMPLATE_BOUNCE_HPP

namespace jt {
namespace ease {
namespace bounce {

float easeIn(float t, float b, float c, float d) noexcept;
float easeOut(float t, float b, float c, float d) noexcept;
float easeInOut(float t, float b, float c, float d) noexcept;

} // namespace bounce
} // namespace ease
} // namespace jt

#endif // JAMTEMPLATE_BOUNCE_HPP
