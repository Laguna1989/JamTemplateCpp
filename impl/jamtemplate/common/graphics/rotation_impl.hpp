#pragma once

namespace jt {

class RotationImpl {
public:
    void doSetRotation(float rot);
    float doGetRotation() const;

private:
    virtual void doRotate(float /*rot*/) = 0;

    float m_rotationInDegree { 0.0f };
};

} // namespace jt
