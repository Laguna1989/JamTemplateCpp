#include "rotation_impl.hpp"

namespace jt {

void RotationImpl::doSetRotation(float rot)
{
    m_rotationInDegree = rot;
    doRotate(m_rotationInDegree);
}

float RotationImpl::doGetRotation() const { return m_rotationInDegree; }

} // namespace jt
