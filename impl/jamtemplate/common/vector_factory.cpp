#include "vector_factory.hpp"
#include <math_helper.hpp>
#include <cmath>

jt::Vector2f jt::VectorFactory::fromCartesian(float x, float y) { return jt::Vector2f { x, y }; }

jt::Vector2f jt::VectorFactory::fromPolar(float r, float phi_in_deg)
{
    float const phi_in_rad = jt::MathHelper::deg2rad(phi_in_deg);
    return jt::Vector2f { r * static_cast<float>(cos(phi_in_rad)),
        r * static_cast<float>(sin(phi_in_rad)) };
}
