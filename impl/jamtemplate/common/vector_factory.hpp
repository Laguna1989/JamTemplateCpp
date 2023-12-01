#ifndef JAMTEMPLATE_VECTOR_FACTORY_HPP
#define JAMTEMPLATE_VECTOR_FACTORY_HPP

#include <vector.hpp>

namespace jt {
struct VectorFactory {
    /// Create a zero vector
    /// \return Vector with (0, 0)
    static constexpr jt::Vector2f zero() noexcept { return jt::Vector2f(); }

    /// Create a cartesian vector
    /// \param x x coordinate
    /// \param y y coordinate
    /// \return (x, y)
    static jt::Vector2f fromCartesian(float x, float y);

    /// Create a polar vector
    /// \param r radius
    /// \param phi_in_deg angle (in degree) [0 - 360]
    /// \return Vector from the polar coordinates
    static jt::Vector2f fromPolar(float r, float phi_in_deg);
};

} // namespace jt
#endif // JAMTEMPLATE_VECTOR_FACTORY_HPP
