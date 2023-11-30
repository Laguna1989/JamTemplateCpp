#ifndef JAMTEMPLATE_EASE_ELASTIC_HPP
#define JAMTEMPLATE_EASE_ELASTIC_HPP

namespace jt {
namespace ease {
namespace elastic {

float easeIn(float t, float b, float c, float d) noexcept;
float easeOut(float t, float b, float c, float d) noexcept;
float easeInOut(float t, float b, float c, float d) noexcept;

} // namespace elastic
} // namespace ease
} // namespace jt

#endif // JAMTEMPLATE_EASE_ELASTIC_HPP
