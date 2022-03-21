#include "rotation_impl.hpp"

void jt::RotationImpl::doSetRotation(float rot)
{
    m_rotationInDegree = rot;
    doRotate(m_rotationInDegree);
}

float jt::RotationImpl::doGetRotation() const { return m_rotationInDegree; }
